#include "world.h"
#include <GL/glut.h>
#include <iostream>
#include "abot.h"
#include "genes/abstract.h"
#include "genes/changeDirAbs.h"
#include "genes/changeDirRel.h"
#include "genes/createBot.h"
#include "genes/eatAbsDir.h"
#include "genes/eatRelDir.h"
#include "genes/flattenedHor.h"
#include "genes/fullAround.h"
#include "genes/giveAbsDir.h"
#include "genes/giveRelDir.h"
#include "genes/isHealthGrow.h"
#include "genes/isMineralGrow.h"
#include "genes/lookAbsDir.h"
#include "genes/lookRelDir.h"
#include "genes/mineralToEnergy.h"
#include "genes/mutate.h"
#include "genes/myHealth.h"
#include "genes/myLevel.h"
#include "genes/myLifeTime.h"
#include "genes/myMineral.h"
#include "genes/photosynthesis.h"
#include "genes/stepAbsDir.h"
#include "genes/stepRelDir.h"

//Объявление статических переменных
int alWorld::_p_v_count;
int alWorld::_p_h_count;
alBot*** alWorld::_bot;
alBot*** alWorld::_bot_cur;

alWorld::alWorld(int p_h_count, int p_v_count, int point_size, int border_size)
    : _point_size(point_size), _border_size(border_size) {
    _p_v_count = p_v_count;
    _p_h_count = p_h_count;
    //Выделяется память для ботов
    //Второй массив нужен для обработки текущего момента мира, чтобы один и тот
    //же бот не активировался несколько раз
    _bot = new alBot**[_p_h_count];
    _bot_cur = new alBot**[_p_h_count];
    for (int i = 0; i < _p_h_count; i++) {
        _bot[i] = new alBot*[_p_v_count];
        _bot_cur[i] = new alBot*[_p_v_count];
        for (int j = 0; j < _p_v_count; j++) {
            _bot[i][j] = NULL;
            _bot_cur[i][j] = NULL;
        }
    }
    //Создаем первого бота
    alBot* new_bot =
        new alBot(_p_h_count / 2, _p_v_count * 1 / 1 - 1, 0.f, 1.f, 0.f);
    this->set_bot(new_bot, new_bot->get_x(), new_bot->get_y());

    //Присваиваем гены
    for (int i = 0; i < 64; i++) {
        alBot::set_gene(i, NULL);
    }
    alBot::set_gene(23, new alGeneChangeDirRel);
    alBot::set_gene(24, new alGeneChangeDirAbs);
    alBot::set_gene(25, new alGenePhotosynthesis);
    alBot::set_gene(26, new alGeneStepRelDir);
    alBot::set_gene(27, new alGeneStepAbsDir);
    alBot::set_gene(28, new alGeneEatRelDir);
    alBot::set_gene(29, new alGeneEatAbsDir);
    alBot::set_gene(30, new alGeneLookRelDir);
    alBot::set_gene(34, new alGeneGiveAbsDir);
    alBot::set_gene(50, alBot::get_gene_by_cmd(34));
    alBot::set_gene(35, new alGeneGiveRelDir);
    alBot::set_gene(51, alBot::get_gene_by_cmd(35));
    alBot::set_gene(36, new alGeneFlattenedHor);
    alBot::set_gene(37, new alGeneMyLevel);
    alBot::set_gene(38, new alGeneMyLifeTime);
    alBot::set_gene(39, new alGeneMyHealth);
    alBot::set_gene(41, new alGeneMyMineral);
    alBot::set_gene(43, new alGeneCreateBot);
    alBot::set_gene(44, new alGeneFullAround);
    alBot::set_gene(45, new alGeneIsHealthGrow);
    alBot::set_gene(47, new alGeneIsMineralGrow);
    alBot::set_gene(48, new alGeneMineralToEnergy);
    alBot::set_gene(49, new alGeneMutate);
}

alWorld::~alWorld() {
    for (int i = 0; i < _p_h_count; i++) {
        delete _bot[i];
    }
    delete _bot;
}

//Отрисовка кадра/Шаг мира
void alWorld::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_POINTS);
    //Копируем расположение текущих ботов
    for (int i = 0; i < _p_h_count; i++) {
        for (int j = 0; j < _p_v_count; j++) {
            _bot_cur[i][j] = _bot[i][j];
        }
    }
    //Проходимся по всем указателям
    for (int i = 0; i < _p_h_count; i++) {
        for (int j = 0; j < _p_v_count; j++) {
            //Если бот существует
            if ((_bot_cur[i][j] != NULL) && (_bot[i][j] != NULL)) {
                //Меняем цвет точки на цвет бота
                glColor3f(_bot_cur[i][j]->get_r(), _bot_cur[i][j]->get_g(),
                          _bot_cur[i][j]->get_b());
                //Делаем шаг
                _bot_cur[i][j]->step();
            } else {
                //Если бот не существует - клетка темно серая
                glColor3f(0.2f, 0.2f, 0.2f);
            }
            //Рисуем клетку
            drawPoint(i, j);
        }
    }
    glEnd();
    glutSwapBuffers();
}

//Отрисовка клетки на нужных координатах
void alWorld::drawPoint(int x, int y) {
    glVertex2f(-1.f + (1.f + 2.f * x) / _p_h_count,
               -1.f + (1.f + 2.f * y) / _p_v_count);
}

//Создание окна
void alWorld::createWindow(int* argc, char** argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(
        this->_p_h_count * (this->_point_size + this->_border_size),
        this->_p_v_count * (this->_point_size + this->_border_size));
    glutCreateWindow("Курсовая работа");
    glPointSize(this->_point_size);
    glutDisplayFunc(this->draw);
    glutIdleFunc(this->draw);

    glutMainLoop();
}

//Получение высоты мира для других классов
int alWorld::get_p_v_count() { return _p_v_count; }
//Получение ширины мира для других классов
int alWorld::get_p_h_count() { return _p_h_count; }

//Возвращает указатель на бота, расположенного по координатам x y
alBot* alWorld::get_bot(int x, int y) {
    if ((x < 0) || (y < 0) || (x >= _p_h_count) || (y >= _p_v_count)) {
        return NULL;
    }
    return _bot[x][y];
}

//Изменяет указатель на бота, расположенного по координатам x y
void alWorld::set_bot(alBot* bot, int x, int y) {
    if ((x < 0) || (y < 0) || (x >= _p_h_count) || (y >= _p_v_count)) {
        return;
    }
    _bot[x][y] = bot;
}

//Удаляет бота
void alWorld::delete_bot(int x, int y) {
    if ((x < 0) || (y < 0) || (x >= _p_h_count) || (y >= _p_v_count)) {
        return;
    }
    delete _bot[x][y];
    _bot[x][y] = NULL;
    _bot_cur[x][y] = NULL;
}

