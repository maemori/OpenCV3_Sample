#----- プロジェクト情報 ----
# プロジェクト名
set(PROJECT_NAME face_detection)
# ビルドターゲットのソースを指定
set(SOURCE_FILES main.cpp)

#----- ビルド設定 -----
# プロジェクトの言語を指定
project(${PROJECT_NAME} CXX)
# コンパイルオプション
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

#----- OpenCVの設定 ----
# OpenCVConfig.cmakeがあるディレクトリを指定（環境に合わせて変更）
SET(OpenCV_DIR "/usr/local/Cellar/opencv3/HEAD-6c12533_4/share/OpenCV")
#SET(OpenCV_DIR "/Users/maemorifumihiro/Develop/dist/opencv/share/OpenCV")
# OpenCvのincludeディレクトリを指定（環境に合わせて変更）
INCLUDE_DIRECTORIES("/usr/local/Cellar/opencv3/HEAD-6c12533_4/include")
#INCLUDE_DIRECTORIES("/Users/maemorifumihiro/Develop/dist/opencv/include")
# [Package]_DIRに指定されたディレクトリを使い検索
FIND_PACKAGE( OpenCV REQUIRED )

#----- ビルド ----
# 対象のソースファイルを設定
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# OpenCVの動的ライブラリをビルドターゲットにリンク
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
