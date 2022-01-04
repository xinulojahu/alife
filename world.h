#ifndef WORLD_H
#define WORLD_H

#include "abot.h"

class alWorld {
   private:
    static int _p_h_count;     // ширина мира
    static int _p_v_count;     // высота мира
    int _point_size;           //размер точки
    int _border_size;          //размер рамки
    static alBot*** _bot;      // массив ботов
    static alBot*** _bot_cur;  // массив ботов для копии

   public:
    alWorld(int p_h_count = 160, int p_v_count = 100, int point_size = 8,
            int border_size = 2);  //конструктор
    ~alWorld();                    //деструктор
    static void draw();            //отрисовка мира/шаг мира
    static void drawPoint(int x, int y);        //отрисовка точки
    void createWindow(int* argc, char** argv);  //создание окна
    static int get_p_v_count();  //получение высоты мира
    static int get_p_h_count();  //получение ширины мира
    static alBot* get_bot(int x, int y);  //получение указателя на бота
    static void set_bot(alBot* bot, int x,
                        int y);  //установка указателя на бота
    static void delete_bot(int x, int y);  //удаление бота
};

#endif
