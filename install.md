# install dwm dependecies
```
sudo pacman -Fy
```
then
```
pacman -F Xft.h
pacman -F Xinerama.h
```
or
```
sudo pacman -S libxft libxinerama
```

# build dwm
```bash
make && sudo make clean install
```
