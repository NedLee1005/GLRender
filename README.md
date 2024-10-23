# OpenGL Render YUYV Buffer.

Use OpenGL Render YUYV Buffer.

##  編譯程式
進入I.MX8 6.6.3 編譯環境
```bash session
$cd GLRender && mkdir build
```
```bash session
$cd build
```
```bash session
$cmake .. && make -j 
```
##  使用方法
* 將編譯出來的 gl_render 及 output3_2.yuv 放進隨身碟內，並用I.MX8執行程式
```bash session
$mount /dev/sda1 /media 
```
```bash session
$./gl_render 
```
##  執行完畢
* I.MX8 畫面顯示魚眼鏡頭畫面則為正常結果