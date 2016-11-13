[TOP](https://github.com/maemori/OpenCV3_Sample/)
----

# [C++] OpenCV3 描画サンプル: 動画の保存

動画を読み込み、リサイズ＆モノクロ変換して動画ファイルの保存を行います。

## 0.内容

保存処理

* cv::VideoWriter writer - ビデオライターの取得
* writer.open - ビデオライタの初期化を確認
* writer << gray - 動画にフレームを追加

保有処理
* cv::VideoCapture - 動画の読み込み
* capture >> frame; - 再生フレームの取得
* cv::resize - リサイズ
* cv::cvtColor(・・・, cv::COLOR_BGR2GRAY); - グレースケール変換

## 1.[サンプルコード](./main.cpp)

### 1.1. 実行イメージ

入力動画:

<video src="sample_01.mp4" width="540" height="960" controls preload></video>

出力動画:

<video src="./etc/Execution_result/output.mp4" width="540" height="960" controls preload></video>

## 2.ビルド

``` bash
cmake .
make
```

## 3.実行

``` bash
./put_text_sample
```

