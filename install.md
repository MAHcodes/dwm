### install dependecies
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

### build
```bash
make && sudo make clean install
```
