/**
 * OpenCV3 描画サンプル: フォントとテキスト
 * go version go1.7.3
 */
package main

import (
	"unsafe"
)

/*
	// OpenCV cooperation.
	// - pkg-config
	#cgo pkg-config: /usr/local/Cellar/opencv3/HEAD-6c12533_4/lib/pkgconfig/opencv.pc
	// - C language foundation include file of opcv
	#include "/usr/local/Cellar/opencv3/HEAD-6c12533_4/include/opencv/cv.h"
	// - HighGUI module include file
	#include "/usr/local/Cellar/opencv3/HEAD-6c12533_4/include/opencv/highgui.h"
*/
import "C"

func main() {
	// 表示する文字列
	text := C.CString("Hi Hello World!")

	// 文字の大きさ
	fontScale := C.double(5.0)

	// 文字の太さ
	thickness := C.int(3)

	// フォントの指定
	var fontFace C.CvFont
	C.cvInitFont(&fontFace, C.CV_FONT_HERSHEY_SCRIPT_COMPLEX, fontScale, 1.0, 0, thickness, 16)

	// 画像マトリックス構造体の作成
	img := C.cvCreateMat(600, 800, C.CV_8UC3)
	C.cvSet(unsafe.Pointer(img), C.cvScalar(200, 150, 100, 0), nil)

	// 文字列表示のベースライン（y座標）
	baseline := C.int(0)

	// 表示文字列のサイズを取得
	var textSize C.CvSize
	C.cvGetTextSize(text, &fontFace, &textSize, &baseline)

	// 中央表示位置の計算
	textOrg := C.cvPoint((img.cols-textSize.width)/2, (img.rows+textSize.height)/2)

	// 文字列をBOXで囲む
	baseline += thickness
	margin := C.int(10)
	C.cvRectangle(unsafe.Pointer(img),
		C.cvPoint(textOrg.x-margin, textOrg.y-textSize.height-margin),
		C.cvPoint(textOrg.x+textSize.width+margin, textOrg.y+margin),
		C.cvScalarAll(50), 0, 8, 0)

	// 表示ベースラインに下線を引く
	C.cvLine(unsafe.Pointer(img),
		C.cvPoint(textOrg.x, textOrg.y+thickness),
		C.cvPoint(textOrg.x+textSize.width, textOrg.y+thickness),
		C.cvScalar(250, 190, 140, 0), 0, 8, 0)

	// 画像マトリックスにテキストを追加
	C.cvPutText(unsafe.Pointer(img), text, textOrg, &fontFace, C.cvScalarAll(250))

	//　ウィンドウの生成
	window_name := C.CString("TestWindow")
	C.cvNamedWindow(window_name, C.CV_WINDOW_AUTOSIZE)

	//　ウィンドウに画像マトリックスを表示
	C.cvShowImage(window_name, unsafe.Pointer(img))

	// ユーザが入力するまで待機
	C.cvWaitKey(0)

	// ウィンドウの破棄（関連するメモリの解放）
	C.cvDestroyAllWindows()

}
