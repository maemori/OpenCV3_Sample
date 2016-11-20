[TOP](https://github.com/maemori/OpenCV3_Sample/)
----

# [C++] OpenCV3 描画サンプル: カメラデバイスからリアルタイム処理

## 1. サンプルの概要

カメラデバイスをオープンして動画リアルタイム処理を行い同時再生、保存を行うサンプル。
処理は[Hough線変換](https://github.com/maemori/OpenCV3_Sample/tree/master/cpp/Image_onversion/hough_line)を流用。
上のサンプルからの変更点は、
* 変更前：cv::VideoCapture capture(inputFilename);
* 変更後：cv::VideoCapture capture(0);


## 2.[サンプルコード](./main.cpp)

## 3. 実行イメージ

入力動画 : カメラからリアルタイム入力

出力動画（クリックでYouTubeの動画が開きます）:

[![出力動画](http://img.youtube.com/vi/qc8cAEZ8kf0/0.jpg)](https://www.youtube.com/watch?v=qc8cAEZ8kf0)

## 4.ビルド

``` bash
cmake .
make
```

## 5.実行

``` bash
./put_text_sample
```
