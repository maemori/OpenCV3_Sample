# OpenCV 3 sample

## 1. Load

### 1.1. Image

画像の読み込みとリサイズ

* [C++](./cpp/load/load_image_sample)

* [Go](./golang/load/load_image_sample)

### 1.2. Video

動画を読み込み、リサイズ＆モノクロ変換して再生

* [C++](./cpp/load/load_video_sample)

* [Go](./golang/load/load_video_sample)

### 1.3. Live

カメラデバイスからライブ動画を処理

* [C++](./cpp/load/load_live_sample)

## 2. Save

### 2.1. Image

画像の保存

* [C++](./cpp/save/save_image_sample)

* [Go](./golang/save/save_image_sample)

### 2.2. Video

動画の保存

* [C++](./cpp/save/save_video_sample)

* [Go](./golang/save/save_video_sample)

## 3. Drawing

### 3.1. Put text

フォントとテキスト

 * [C++](./cpp/drawing/put_text_sample)

 * [Go](./golang/drawing/put_text_sample)

## 4. Image onversion

### 4.1. Canny

Cannyエッジ検出器

 * [C++](./cpp/Image_onversion/canny)
 
 * [Go](./golang/Image_onversion/canny)
 
### 4.2. BilateralFilter

平準化:バイラテラルフィルター

 * [C++](./cpp/Image_onversion/bilateral_filter)

  
### 4.3. HoughLinesP

Hough線変換(PPHT:Progressive Probabilistic Hough Transform)

 * [C++](./cpp/Image_onversion/hough_line)
 
## 5. Object detection

### 5.1 Face detection

カメラから入力されたライブ動画から顔を識別し置換用の画像で置き換えます。処理結果はリアルタイムに表示し動画ファイルとしても保存を行います。

 * [C++](./cpp/object_detection/face_detection)
 
### 5.2 Cat face detection

動画から猫をを識別します。処理結果はリアルタイムに表示し動画ファイルとしても保存を行います。

 * [C++](./cpp/object_detection/cat_detection)