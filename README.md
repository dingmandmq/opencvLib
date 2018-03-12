# opencvLib
## 包含opencv的静态库
### 使用opencv实现对图片明水印、暗水印、信息存储像素、傅里叶转换等
### 不是太懂得可以查看下文章：[OpenCV-图像处理-频域手段添加盲水印](https://www.jianshu.com/p/62e52c4ab5c4)
#### 调用方法
```
//添加使用傅里叶转换添加的标示
- (void)addVisibleMarkText{
//     NSString *imagePath = [NSHomeDirectory() stringByAppendingString:saveimageName];
//     UIImage *imagetmp = [UIImage imageWithContentsOfFile:imagePath];
cv::Mat orignMat = [[OpenCVUtil share] cvMatFromUIImage:self.getImage? self.getImage :[UIImage imageNamed:imageName]];//
cv::Mat getMat = [[OpenCVUtil share] addVisibleMarkText:orignMat blindMarkText:@"XXXX" point:cv::Point(45,45) fontSize:0.8 scalar:CV_RGB(255,255,255)];
UIImage *image = [[OpenCVUtil share] UIImageFromCVMat:getMat];
self.imgView.image = image;

}

//去掉使用傅里叶转换添加的标示
- (void)removeVisibleMarkText {

cv::Mat orignMat = [[OpenCVUtil share] cvMatFromUIImage:self.imgView.image];//
cv::Mat getMat = [[OpenCVUtil share] removeVisibleMarkText:orignMat scalar:CV_RGB(255,255,255)];
UIImage *image = [[OpenCVUtil share] UIImageFromCVMat:getMat];
self.imgView.image = image;
}

// 一些信息添加到矩阵后生成的图
- (void)matrixAdd {
//傅里叶打水印
cv::Mat orignMat = [[OpenCVUtil share] cvMatFromUIImage:self.getImage? self.getImage :[UIImage imageNamed:imageName]];//
//    [[OpenCVUtil share] transformImageWithText:orignMat blindMarkText:@"Test" point:cv::Point(45,45) fontSize:0.8 scalar:CV_RGB(255,255,255)];
//    cv::Mat cvMat = [[OpenCVUtil share] antitransformImage];
UIImage *image = [[OpenCVUtil share] UIImageFromCVMat:orignMat];

//把打水印的图片添加信息
cv::Mat matTmp = [[OpenCVUtil share] addMessageMatrixToOriginalMatRow:orignMat messageDic:@{@"imageMD5":[[OpenCVUtil share] getImageMatrixMD5String:orignMat],@"data":@"data"}];
self.imgView.image = [[OpenCVUtil share] UIImageFromCVMat:matTmp];

NSString *imagePath = [NSHomeDirectory() stringByAppendingString:saveimageName];
//把图片直接保存到指定的路径（同时应该把图片的路径imagePath存起来，下次就可以直接用来取）
[UIImagePNGRepresentation(self.imgView.image) writeToFile:imagePath atomically:YES];

UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"温馨提示" message:@"添加完成" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
[alertView show];

}
//// 从矩阵去掉信息后还原的图
- (void)matrixRemove {
//从保存的打水印并添加信息的图片获取信息并对比
NSString *imagePath = [NSHomeDirectory() stringByAppendingString:saveimageName];
UIImage *image = [UIImage imageWithContentsOfFile:imagePath];
//    UIImage *image = [UIImage imageNamed:imageName];
cv::Mat orignMat = [[OpenCVUtil share] cvMatFromUIImage:image];
[[OpenCVUtil share] removeMessageMatrixToOriginalMatRow:orignMat getRestoreData:^(NSDictionary *dataDic, cv::Mat restoreMat) {

NSLog(@"%@",dataDic);
UIImage *image = [[OpenCVUtil share] UIImageFromCVMat:restoreMat];
self.imgView.image = image;

if ([dataDic[@"imageMD5"] isEqualToString:[[OpenCVUtil share] getImageMatrixMD5String:restoreMat]]) {
UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"温馨提示" message:@"对比success" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
[alertView show];
}
}];
}

```
####  核心代码

```
+ (instancetype)share;
/**
*
*  MatFromUIImage
*
*  @param  image  传入图片
*
*/
-(cv::Mat)cvMatFromUIImage:(UIImage *)image;
/**
*
*  UIImageFromCVMat
*
*  @param  cvMat  传入图片Mat
*
*/
-(UIImage *)UIImageFromCVMat:(cv::Mat)cvMat;

/**
*
*  傅里叶dft转换添加水印Text到频域
*
*  @param  image  传入图片Mat
*  @param  blindMarkText 水印文字
*  @param  point 文字位置
*  @param  fontSize 文字大小
*  @param  scalar    颜色
*
*/
- (void)transformImageWithText:(cv::Mat) image blindMarkText:(NSString *) blindMarkText point:(cv::Point) point fontSize:(double)fontSize scalar:(cv::Scalar) scalar ;
/**
*
*  傅里叶dft转换显示频域
*
*  @param  image  传入图片Mat
*
*/
- (cv::Mat)transformImage:(cv::Mat)image;
/**
*
*  傅里叶idft逆转换显示图片
*
*/
- (cv::Mat)antitransformImage;
/**
* 为加快傅里叶变换的速度，对要处理的图片尺寸进行优化
*
* @param image
*            the {@link Mat} to optimize
* @return the image whose dimensions have been optimized
*/
- (cv::Mat)optimizeImageDim:(cv::Mat)image;
/**
*
*  创建优化量级
*
*  @param  complexImage  传入图片Mat
*
*/
- (cv::Mat)createOptimizedMagnitude:(cv::Mat)complexImage;
/**
*
*  转换DFT
*
*  @param  image  传入图片Mat
*
*/
- (void)shiftDFT:(cv::Mat)image;
- (cv::Mat)extractImage;
/**
*
*  添加明水印
*
*  @param  image  传入图片Mat
*  @param  blindMarkText 水印文字
*  @param  point 文字位置
*  @param  fontSize 文字大小
*  @param  scalar    颜色
*
*/
- (cv::Mat)addVisibleMarkText:(cv::Mat) image blindMarkText:(NSString *) blindMarkText point:(cv::Point) point fontSize:(double)fontSize scalar:(cv::Scalar) scalar;
/**
*
*  删除明水印
*
*  @param  image  传入图片Mat
*  @param  blindMarkText 水印文字
*  @param  point 文字位置
*  @param  fontSize 文字大小
*  @param  scalar    颜色
*
*/
- (cv::Mat)removeVisibleMarkText:(cv::Mat) image scalar:(cv::Scalar) scalar ;
/**
*
*  添加Message到图像矩阵
*
*  @param  oriMat  传入图片Mat
*  @param  dataDic 传入的dataDic
*
*/
- (cv::Mat)addMessageMatrixToOriginalMatRow:(cv::Mat) oriMat messageDic:(NSDictionary *)dataDic;
/**
*
*  删除图像中添加的Message矩阵
*
*  @param  oriMat  传入图片Mat
*  @response  dataDic 返回的信息
*  @response  restoreMat 返回的Mat
*
*/
- (void)removeMessageMatrixToOriginalMatRow:(cv::Mat)oriMat getRestoreData:(void(^)(NSDictionary *dataDic,cv::Mat restoreMat))successBlock ;
/**
*
*  对图片base64+Md5String
*
*  @param  img  图片
*
*/
-(NSString *)base64ToMd5WithImage:(UIImage *)img path:(NSString *)path ;
/**
*
*  MD5加密
*
*  @param  mdStr  未加密的String
*
*/
- (NSString *)MD5:(NSString *)mdStr;

/**
*
*  dictionary转换成JsonString
*
*  @param  infoDict  dictionary
*
*/
- (NSString*)convertToJSONData:(id)infoDict;
/**
*
*  JsonString转换为dictionary
*
*/
- (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString;
- (NSString *)getImageMatrixMD5String:(cv::Mat)mat ;
/**
*
* 原生添加水印文字
*
*  @param  img  图片
*
*/
- (UIImage *)addimageWithTitle:(NSString *)title fontSize:(CGFloat)fontSize image:(UIImage *)image rectX:(CGFloat )rectX rectY:(CGFloat )rectY;
/**
*
* 宽高比压缩
*
*  @param  img  图片
*
*/
- (UIImage *)imageWithImage:(UIImage*)image
scaledToSize:(CGSize)newSize;
/**
*
* 全部处理过后的Image
*
*  @param  img  图片
*
*/
- (UIImage *)getProcessedFinalImageWithoriginalImage:(UIImage *)originalImg note:(NSString *)noteStr address:(NSString *)addressStr fillData:(NSDictionary *)messageDic;

-(void)savephotoToDocumentFileImage:(UIImage *)image;
-(UIImage *)getphotoFromDocumentFile;
-(void)deleteDocumentFile;
```
