//
//  OpenCVUtil.h
//  OpenCViOSTest
//
//  Created by Miaoz on 2017/6/18.
//  Copyright © 2017年 Miaoz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <opencv2/opencv.hpp>
//
//#import "core.hpp"
//
//#import "<opencv2/"imgcodecs.hpp>
//#import <opencv2/imgproc.hpp>
//#import <opencv2/imgproc/types_c.h>
//#import <opencv2/imgproc/imgproc_c.h>
//
//#import <opencv2/features2d.hpp>
//#import <opencv2/calib3d.hpp>
//#import <opencv2/objdetect.hpp>
//#import <opencv2/highgui.hpp>
//#import <opencv2/objdetect/objdetect.hpp>
//
//#import <opencv2/videoio/videoio_c.h>
//#import <opencv2/videoio/cap_ios.h>

#include <iostream>


@interface OpenCVUtil : NSObject
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
@end
