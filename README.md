# IT_Academy
## Введение
Данный прект был создан специально для в рамках курса ["Профессиональная разработка игр на C++"](https://www.it-academy.by/course/c-game-developer/game-developer/ "Course") от [IT Academy](https://www.it-academy.by/ "IT Academy").

Со временем, сюда будут добавлятся новые работы, связанные с обучением.

## Установка
#### **Debian Linux**
```bash
$ git clone git@github.com:AA55hex/IT_Academy.git
$ sudo apt install cmake gcc ninja-build
$ cd IT_Academy/Task_1 & mkdir build & cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=DEBUG ..
$ cmake --build .
$ cmake --install .
$ Test hello world
```
## Решение проблем
#### Ошибка: "Tutorial: error while loading shared libraries: libMathFunctions.so: cannot open shared object file: No such file or directory"

**Решение**
- создайте файл .conf в директории /etc/ld.so.conf.d/ и запишите в него путь "/usr/local/lib"
- обновите конфигурацию

**Пример:**
```bash
$ sudo bash -c  "echo /usr/local/lib >> /etc/ld.so.conf.d/local.conf"
$ sudo ldconfig
```
---
