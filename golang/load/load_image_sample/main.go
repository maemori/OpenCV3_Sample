/**
 * OpenCV3 読込サンプル: 画像の読み込みとリサイズ
 * go version go1.7.3
 */
package main

import (
	"os"
	"unsafe"
)

/*
	// OpenCV cooperation.
	// - pkg-config
	#cgo pkg-config: /usr/local/Cellar/opencv3/HEAD-6c12533_4/lib/pkgconfig/opencv.pc
	// - include file
	#include "/usr/local/Cellar/opencv3/HEAD-6c12533_4/include/opencv/highgui.h"
	#include "/usr/local/Cellar/opencv3/HEAD-6c12533_4/include/opencv2/imgcodecs/imgcodecs_c.h"
*/
import "C"

func main() {

	// 画像のファイル
	filename := C.CString("sample_01.jpg")

	// 画像を読み込み
	img := C.cvLoadImage(filename, C.CV_LOAD_IMAGE_COLOR)

	// 画像を縮小（元の画像の20%）
	resizeImg := C.cvCreateMat(img.height/5, img.width/5, C.CV_8UC3)
	C.cvResize(unsafe.Pointer(img), unsafe.Pointer(resizeImg), C.CV_INTER_CUBIC)

	//　ウィンドウの生成
	window_name := C.CString("TestWindow")
	C.cvNamedWindow(window_name, C.CV_WINDOW_AUTOSIZE)

	//　ウィンドウに画像を表示
	C.cvShowImage(window_name, unsafe.Pointer(resizeImg))

	// ユーザが入力するまで待機
	C.cvWaitKey(0)

	// ウィンドウの破棄（関連するメモリの解放）
	C.cvDestroyAllWindows()

	// 終了
	os.Exit(0)

}
