# 简易中文分词例子

### How to build

```
git clone https://github.com/thelostpeace/word_seg.git
cd word_seg
make
```

```
到offline目录下
sh train.sh
跑分词模型
```

```
修改crf_model.h里
#define CRF_MODEL_FILE "model/crf_model" 
来修改crf分词模型地址
```

```
编译完之后直接运行
./word_seg

运行client.py
./client.py

>>> (type EXIT to quit) q
>>> ["q"]
>>> (type EXIT to quit) 等下班了，我要坐398路公交车去五道口地铁站。
>>> ["等", "下班", "了", "，", "我", "要", "坐", "398路", "公交车", "去", "五道口", "地铁站", "。"]
>>> (type EXIT to quit)
```

Enjoy!!!
