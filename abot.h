#ifndef BOTSEAWEED_H
#define BOTSEAWEED_H

#include "genes/abstract.h"

class alBot {
   private:
    int _x;          //координата по x
    int _y;          //координата по y
    int _hp;         //хп/энергия/здоровье бота
    int _life_time;  //время жизни бота
    int _mineral;    //количество минералов
    int _dir;  //текущее направление, куда смотрит бот
    float _r;                  //красный
    float _g;                  //зеленый
    float _b;                  //синий
    static alGene* _gene[64];  //набор генов, общий для всех ботов
    unsigned char _adr;  //указатель на ген
    unsigned char _command[64];  //массив генов конкретного бота
    bool _alive;                 //флаг живой ли бот

   public:
    alBot(int x, int y, int hp = 100, int min = 0, float r = 0.8f,
          float g = 0.8f, float b = 0.8f);
    alBot(int x, int y, float r, float g, float b);
    void step();
    void incCmdAdr(int incValue);
    int get_x();
    void set_x(int value);
    int get_y();
    void set_y(int value);
    int get_hp();
    void set_hp(int value);
    int get_life_time();
    int get_mineral();
    void set_mineral(int value);
    int get_dir();
    void set_dir(int value);
    float get_r();
    void set_r(float value);
    float get_g();
    void set_g(float value);
    float get_b();
    void set_b(float value);
    alGene* get_gene(int id);
    static alGene* get_gene_by_cmd(int id);
    static void set_gene(int id, alGene* gene);
    unsigned char get_adr();
    void set_adr(unsigned char value);
    unsigned char get_command(int id);
    void set_command(int id, unsigned char value);
    bool get_alive();
    void set_alive(bool value);

    unsigned char get_param();
    int look(int dir);
    int give(int dir);
    int eat(int dir);
    int move(int dir);
    void burnNew();
    void mutate();

    int get_new_x(int dir);
    int get_new_y(int dir);

    void goRed(float value);
    void goGreen(float value);
    void goBlue(float value);
};

#endif
