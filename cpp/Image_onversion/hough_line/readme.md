[TOP](https://github.com/maemori/OpenCV3_Sample/)
----

# [C++] OpenCV3 描画サンプル: Hough線変換

プログレッシブな確率的Hough変換(PPHT:Progressive Probabilistic Hough Transform)を用いて動画から直線の抽出を行います。


## 1. サンプルの概要

1. 動画のフレームの読み込み
2. 画像を縮小(resize)
3. グレースケールに変換(cvtColor)
4. 平準化の実行:バイラテラルフィルタ(bilateralFilter)
5. エッジ検出器の実行:Canny(Canny)
6. Hough線変換:プログレッシブな確率的Hough変換(HoughLinesP)
7. 処理結果のフレームを再生し保存

## 2.[サンプルコード](./main.cpp)

## 3. 実行イメージ

入力動画（クリックでYouTubeの動画が開きます）:

[![入力動画](http://img.youtube.com/vi/UDPQthJe7cg/0.jpg)](https://www.youtube.com/watch?v=UDPQthJe7cg)

出力動画（クリックでYouTubeの動画が開きます）:

[![出力動画](http://img.youtube.com/vi/MpB86yd_qqY/0.jpg)](https://www.youtube.com/watch?v=MpB86yd_qqY)

## 4.ビルド

``` bash
cmake .
make
```

## 5.実行

``` bash
./put_text_sample
```
