[TOP](https://github.com/maemori/OpenCV3_Sample/)
----

# [C++] OpenCV3 描画サンプル: Cannyエッジ検出器

動画を読み込み、リサイズ＆モノクロ変換を行いエッジ抽出を行い処理結果を再生（処理結果を動画ファイルに保存）。

## Cannyエッジ検出器の概要
1986年にJ.Cannyに寄って洗練されたエッジ検出器。  

個々のエッジの候補値ピクセルから輪郭を作り上げようとします。  
この輪郭はヒステリシス閾値をピクセルに適用することで形成されます。  
ヒステリスス閾値は上限と下限を指定し、ピクセルが上限の閾値より大きい勾配を持っているっ場合はエッジのピクセルとして受け入れられます。
下限の閾値より小さいと破棄され、間の場合は高い閾値も上のピクセルと繋がっている場合だけ受け入れられます。
上限と下限の推奨比率は2:1、3:1の間です。  
また、正方形フィルタの幅であるアパーチャの値を指定します。アパーチャの値は1、3、5、7がサポートされています。
 
## 0.サンプルの内容

エッジ抽出処理

* cvCanny - Cannyエッジ検出器の実行

保有処理

* cvCreateFileCapture - 動画の読み込み
* cvQueryFrame - 再生フレームの取得
* cvResize - リサイズ
* cvCvtColounsafe(・・・, C.CV_BGR2GRAY)r - グレースケール変換
* cvCreateVideoWriter - ビデオライターの取得
* cvWriteFrame - 動画にフレームを追加

## 1.[サンプルコード](./main.go)


### 1.1. 実行イメージ

入力動画（クリックでYouTubeの動画が開きます）:

[![入力動画](http://img.youtube.com/vi/UDPQthJe7cg/0.jpg)](https://www.youtube.com/watch?v=UDPQthJe7cg)

出力動画（クリックでYouTubeの動画が開きます）:

[![出力動画](http://img.youtube.com/vi/w7DHFM1D1zU/0.jpg)](https://www.youtube.com/watch?v=w7DHFM1D1zU)

## 2.ビルド

``` bash
cmake .
make
```

## 3.実行

``` bash
./put_text_sample
```
