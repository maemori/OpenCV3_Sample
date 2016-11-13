[TOP](https://github.com/maemori/OpenCV3_Sample/)
----

# [C++] OpenCV3 描画サンプル: 動画を読み込み、リサイズ＆モノクロ変換して再生

## 0.内容

* cv::VideoCapture - 動画の読み込み
* capture >> frame; - 再生フレームの取得
* cv::resize - リサイズ
* cv::cvtColor(・・・, cv::COLOR_BGR2GRAY); - グレースケール変換

## 1.[サンプルコード](./main.cpp)

## 2.ビルド

``` bash
cmake .
make
```

## 3.実行

``` bash
./put_text_sample
```

![実行結果イメージ](./etc/Execution_result/sample_01.png)
