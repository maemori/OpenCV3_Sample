[TOP](https://github.com/maemori/OpenCV3_Sample/)
----

# [C++] OpenCV3 物体認識サンプル: リアルタイムねこ認識

カメラから入力されたライブ動画からネコを識別し置換用の画像で置き換えます。処理結果はリアルタイムに表示し動画ファイルとしても保存を行います。

## 1. サンプルの概要

処理順序:
1. 動画のフレームの読み込み
2. 画像を縮小(resize)
3. グレースケールに変換(cvtColor)
4. 物体検出(detectMultiScale)
5. 検出された物体を加工


## 2.[サンプルコード](./main.cpp)

## 3. 実行イメージ

入力動画 : カメラからリアルタイム入力

出力動画（クリックでYouTubeの動画が開きます）:

[![出力動画](http://img.youtube.com/vi/dOA8wiAfHr8/0.jpg)](https://www.youtube.com/watch?v=dOA8wiAfHr8)

## 4.ビルド

``` bash
cmake .
make
```

## 5.実行

``` bash
./put_text_sample
```
