# pong_game

To play interactive pong, you will need to install the lncurses library

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```
 After installation you need verify installation

```bash
 dpkg -L libncurses-dev libncurses5-dev libncursesw5-dev
```

 Next step is compile the file with flag -lncurses

```bash
gcc interactive_pong.c -lncurses
```

