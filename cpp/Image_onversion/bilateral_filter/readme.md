[TOP](https://github.com/maemori/OpenCV3_Sample/)
----

# [C++] OpenCV3 描画サンプル: 平準化・バイラテラルフィルター.

画像平準化の一つ。エッジ情報を保持しながら画像の平準化を行います。  
入力された動画を当フィルタを使用し平準化を行いその結果を再生・保存を行います。
 
## 0.サンプルの内容

エッジ抽出処理
* cv::bilateralFilter - 平準化・バイラテラルフィルター

保有処理
* cv::VideoCapture - 動画の読み込み
* capture >> frame; - 再生フレームの取得
* cv::resize - リサイズ
* cv::cvtColor(・・・, cv::COLOR_BGR2GRAY); - グレースケール変換
* cv::VideoWriter writer - ビデオライターの取得
* writer.open - ビデオライターの初期化を確認
* writer << gray - 動画にフレームを追加
* cv::Canny - Cannyエッジ検出器の実行

## 1.[サンプルコード](./main.cpp)


### 1.1. 実行イメージ

入力動画（クリックでYouTubeの動画が開きます）:

[![入力動画](http://img.youtube.com/vi/UDPQthJe7cg/0.jpg)](https://www.youtube.com/watch?v=UDPQthJe7cg)

出力動画（クリックでYouTubeの動画が開きます）:

[![出力動画](http://img.youtube.com/vi/ycCIoXkgauY/0.jpg)](https://www.youtube.com/watch?v=ycCIoXkgauY)

## 2.ビルド

``` bash
cmake .
make
```

## 3.実行

``` bash
./put_text_sample
```
