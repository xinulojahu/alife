#include "abot.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "world.h"

//В случае ошибок
#define DEBUG false

//Объявляется статическая переменная для генов
alGene* alBot::_gene[64];

alBot::alBot(int x, int y, int hp, int min, float r, float g, float b)
    : _x(x),
      _y(y),
      _hp(hp),
      _life_time(0),
      _mineral(min),
      _dir(rand() % 8),
      _r(r),
      _g(g),
      _b(b),
      _adr(0),
      _alive(true) {
    for (int i = 0; i < 64; i++) {
        _command[i] = 25;
    }
}
alBot::alBot(int x, int y, float r, float g, float b)
    : alBot(x, y, 100, 0, r, g, b) {}

//Шаг бота
void alBot::step() {
    //Если бот мертв, то передвигаем его вниз и выходим
    if (this->get_alive() == false) {
        this->move(5);
        return;
    }

    //Максимум может быть выполнено 16 генов
    for (int i = 0; (i < 16); i++) {
        //Если ген не существует, тогда это безусловный переход
        if (this->get_gene(this->get_adr()) == NULL) {
            incCmdAdr(this->get_command(this->get_adr()));
            break;
        }
        //Для ошибок
        if (DEBUG) {
            std::cout << this->get_x() << " " << this->get_y() << ": USE "
                      << int(this->get_command(this->get_adr())) << std::endl;
        }
        //Если ген существует, то выполняется команды внутри и выходит из цикла
        if (this->get_gene(this->get_adr())->doGene(this)) {
            break;
        }
    }
    //Увеличиваем время жизни бота на 1
    this->_life_time += 1;
    //Если бот живет уже 1000 тиков, то он умирает
    if (this->_life_time > 1000) {
        this->set_hp(0);
    }
    //Если у бота более 999 хп, то нужно дать потомства
    if (this->get_hp() > 999) {
        this->burnNew();
    }

    //Уменьшаем текущие хп на 3
    this->set_hp(this->get_hp() - 3);
    //Если хп < 1, то бот умер
    if (this->get_hp() < 1) {
        //Ставим флаг смерти
        this->set_alive(false);
        //Ставим серый цвет
        this->set_r(0.5f);
        this->set_g(0.5f);
        this->set_b(0.5f);
        return;
    }

    //Увеличиваем количество минералов, если бот внизу, но не более 1000
    if (this->get_y() < alWorld::get_p_v_count() / 2) {
        int minAdd = 1;
        if (this->get_y() < alWorld::get_p_v_count() / 6 * 2) {
            minAdd++;
        }
        if (this->get_y() < alWorld::get_p_v_count() / 6) {
            minAdd++;
        }
        this->set_mineral((this->get_mineral() + minAdd) % 1000);
    }
}

//Переход к другой команде
void alBot::incCmdAdr(int incValue) { set_adr((get_adr() + incValue) % 64); }

//функции для работы с приватными переменными из других кллассов
int alBot::get_x() { return this->_x; }
void alBot::set_x(int value) { this->_x = value; }
int alBot::get_y() { return this->_y; }
void alBot::set_y(int value) { this->_y = value; }
int alBot::get_hp() { return this->_hp; }
void alBot::set_hp(int value) { this->_hp = value; }
int alBot::get_life_time() { return this->_life_time; }
int alBot::get_mineral() { return this->_mineral; }
void alBot::set_mineral(int value) { this->_mineral = value; }
int alBot::get_dir() { return this->_dir; }
void alBot::set_dir(int value) { this->_dir = value; }
float alBot::get_r() { return this->_r; }
void alBot::set_r(float value) { this->_r = value; }
float alBot::get_g() { return this->_g; }
void alBot::set_g(float value) { this->_g = value; }
float alBot::get_b() { return this->_b; }
void alBot::set_b(float value) { this->_b = value; }
alGene* alBot::get_gene(int id) { return this->_gene[this->get_command(id)]; }
alGene* alBot::get_gene_by_cmd(int id) { return alBot::_gene[id]; }
void alBot::set_gene(int id, alGene* gene) { alBot::_gene[id] = gene; }
unsigned char alBot::get_adr() { return this->_adr; }
void alBot::set_adr(unsigned char value) { this->_adr = value; }
unsigned char alBot::get_command(int id) { return this->_command[id % 64]; }
void alBot::set_command(int id, unsigned char value) {
    this->_command[id % 64] = value % 64;
}
bool alBot::get_alive() { return this->_alive; }
void alBot::set_alive(bool value) { this->_alive = value; }

//Получение параметра для некоторых генов
unsigned char alBot::get_param() {
    return this->get_command((this->get_adr() + 1) % 64);
}

// Направления dir
// 0 | 1 | 2
// 7 | * | 3
// 6 | 5 | 4
//
//Посмотреть в направлении dir
int alBot::look(int dir) {
    //Получение координат для dir
    int dx = get_new_x(dir);
    int dy = get_new_y(dir);

    //Если там граница карты, то возвращаем 3
    if ((dy < 0) || (dy >= alWorld::get_p_v_count())) {
        return 3;
    }
    //Если там пусто, то возвращаем 2
    if (alWorld::get_bot(dx, dy) == NULL) {
        return 2;
    }
    //Если там мертвый бот, то возвращаем 4
    if (alWorld::get_bot(dx, dy)->get_alive() == false) {
        return 4;
    }
    //Если там живой бот, то возвращаем 5
    return 5;
}

//Дать энергию боту по направлению dir
int alBot::give(int dir) {
    //Смотрим в этом направлении
    int ret = this->look(dir);
    //Если там не живой бот, то выходим
    if (ret < 5) {
        return ret;
    }
    //Получаем координаты
    int dx = get_new_x(dir);
    int dy = get_new_y(dir);

    //Передаем четверть хп другому боту
    int hp = this->get_hp();
    this->set_hp(this->get_hp() - hp / 4);
    alWorld::get_bot(dx, dy)->set_hp(alWorld::get_bot(dx, dy)->get_hp() +
                                     hp / 4);

    //Передаем четверть минералов другому боту
    int min = this->get_mineral();
    this->set_mineral(this->get_mineral() - min / 4);
    alWorld::get_bot(dx, dy)->set_mineral(
        (alWorld::get_bot(dx, dy)->get_mineral() + min / 4) % 1000);
    //возвращаем 5
    return 5;
}

//Съесть по направлению dir
int alBot::eat(int dir) {
    //Смотрим в этом направлении
    int ret = this->look(dir);
    //Если там нет бота, то выходим
    if (ret < 4) {
        return ret;
    }
    //на попытку съесть тратим 4 энергии
    this->set_hp(this->get_hp() - 4);
    //Получаем координаты
    int dx = get_new_x(dir);
    int dy = get_new_y(dir);

    //Если бот мертвый, то съедаем его и выходим
    if (alWorld::get_bot(dx, dy)->get_alive() == false) {
        alWorld::delete_bot(dx, dy);
        //За мертвого бота получаем 120 энергии
        this->set_hp(this->get_hp() + 120);
        // и краснеем
        this->goRed(0.4);
        return 4;
    }

    //Если бот живой
    //Минары бота
    int mymin = this->get_mineral();
    //Минералы цели
    int othermin = alWorld::get_bot(dx, dy)->get_mineral();
    //Потенциальные хп
    int hpAdd = alWorld::get_bot(dx, dy)->get_hp() * 2 / 3;
    //Если минеры бота больше, чем минералы цели
    if (mymin >= othermin) {
        //то отнимаем у бота минералы (Типо стесал зубы о панцирь)
        this->set_mineral(mymin - othermin);
        //и съедаем бота
        this->set_hp(this->get_hp() + hpAdd);
        alWorld::delete_bot(dx, dy);
        //Краснеем
        goRed(float(hpAdd) / 250.f);
    } else if (this->get_hp() >= 2 * othermin) {
        //Если минералов не хватает, то тратит свои хп, чтобы прокусить
        othermin -= mymin;
        hpAdd -= 2 * othermin;
        //И съедает
        this->set_hp(this->get_hp() + hpAdd);
        alWorld::delete_bot(dx, dy);
        goRed(float(hpAdd) / 250.f);

    } else {
        //Если и хп не хватило, то бот умирает, а у цели уменьшаются минералы
        alWorld::get_bot(dx, dy)->set_mineral(othermin - mymin -
                                              this->get_hp() / 2);
        this->set_hp(0);
    }
    return 5;
}

//Смещение бота
int alBot::move(int dir) {
    //Смотрим в это направление
    int ret = this->look(dir);
    //Если там не пустая ячейка, то выходим
    if (ret != 2) {
        return ret;
    }
    //Получаем координатв
    int dx = get_new_x(dir);
    int dy = get_new_y(dir);
    //перемещаемся
    alWorld::set_bot(this, dx, dy);
    alWorld::set_bot(NULL, this->get_x(), this->get_y());
    this->set_x(dx);
    this->set_y(dy);
    return 2;
}

//рождение нового бота
void alBot::burnNew() {
    //Уменьшается количество хп на 150
    this->set_hp(this->get_hp() - 150);
    //Если бот умер то возвращаемся
    if (this->get_hp() <= 0) {
        return;
    }

    int dx;
    int dy;
    //Ищем пустое поле вокруг
    for (int i = 0; i < 8; i++) {
        dx = get_new_x(i);
        dy = get_new_y(i);
        //Если она существует
        if ((dy >= 0) && (dy < alWorld::get_p_v_count())) {
            if (alWorld::get_bot(dx, dy) == NULL) {
                //Создаем нового бота
                alBot* bot =
                    new alBot(dx, dy, this->get_hp() / 2, this->get_hp() / 2,
                              this->get_r(), this->get_g(), this->get_b());
                //Добавляем в массив ботов
                alWorld::set_bot(bot, dx, dy);
                //Если не получилось, то удаляем бота и выходим
                if (alWorld::get_bot(dx, dy) == NULL) {
                    delete bot;
                    return;
                }
                //копируем геном
                for (int j = 0; j < 64; j++) {
                    alWorld::get_bot(dx, dy)->set_command(j,
                                                          this->get_command(j));
                }
                //С вероятностью 1/4 мутируем
                if (rand() % 4 == 0) {
                    alWorld::get_bot(dx, dy)->mutate();
                }

                //Уменьщаем хп и минералы в 2 раза (поделились с потомком)
                this->set_hp(this->get_hp() / 2);
                this->set_mineral(this->get_mineral() / 2);
                return;
            }
        }
    }
    //Если пустого поля нет, то выходим
    // this->set_hp(0);
    return;
}

//Мутация (случайный ген заменяется на случайное значение)
void alBot::mutate() {
    srand(time(NULL) * rand());
    this->set_command(rand() % 64, rand() % 64);
}

// Направления dir
// 0 | 1 | 2
// 7 | * | 3
// 6 | 5 | 4
//
//Получение x по направлению
int alBot::get_new_x(int dir) {
    int dx = 0;
    switch (dir % 8) {
        case 2:
        case 3:
        case 4:
            dx = 1;
            break;
        case 0:
        case 6:
        case 7:
            dx = -1;
            break;
    }
    dx += this->get_x();
    if (dx < 0) {
        dx = alWorld::get_p_h_count() - 1;
    }
    if (dx >= alWorld::get_p_h_count()) {
        dx = 0;
    }
    return dx;
}

//Получение y по направлению
int alBot::get_new_y(int dir) {
    int dy = 0;
    switch (dir % 8) {
        case 0:
        case 1:
        case 2:
            dy = 1;
            break;
        case 4:
        case 5:
        case 6:
            dy = -1;
            break;
    }
    dy += this->get_y();
    return dy;
}

void alBot::goRed(float value) {
    value /= 5;
    if (this->get_r() + value >= 1) {
        this->set_r(1.f);
    } else {
        this->set_r(this->get_r() + value);
    }
    if (this->get_g() - value / 2 <= 0) {
        this->set_g(0.f);
    } else {
        this->set_g(this->get_g() - value / 2);
    }
    if (this->get_b() - value / 2 <= 0) {
        this->set_b(0.f);
    } else {
        this->set_b(this->get_b() - value / 2);
    }
}

void alBot::goGreen(float value) {
    value /= 5;
    if (this->get_g() + value >= 1) {
        this->set_g(1.f);
    } else {
        this->set_g(this->get_g() + value);
    }
    if (this->get_r() - value / 2 <= 0) {
        this->set_r(0.f);
    } else {
        this->set_r(this->get_r() - value / 2);
    }
    if (this->get_b() - value / 2 <= 0) {
        this->set_b(0.f);
    } else {
        this->set_b(this->get_b() - value / 2);
    }
}

void alBot::goBlue(float value) {
    value /= 5;
    if (this->get_b() + value >= 1) {
        this->set_b(1.f);
    } else {
        this->set_b(this->get_b() + value);
    }
    if (this->get_g() - value / 2 <= 0) {
        this->set_g(0.f);
    } else {
        this->set_g(this->get_g() - value / 2);
    }
    if (this->get_r() - value / 2 <= 0) {
        this->set_r(0.f);
    } else {
        this->set_r(this->get_r() - value / 2);
    }
}
