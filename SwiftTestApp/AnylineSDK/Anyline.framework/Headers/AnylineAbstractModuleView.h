//
//  AnylineAbstractModuleView.h
//  
//
//  Created by Daniel Albertini on 01/07/15.
//
//

#import <UIKit/UIKit.h>
#import "ALFlashButton.h"
#import "ALTorchManager.h"
#import "ALUIConfiguration.h"
#import "ALCoreController.h"
#import "ALMotionDetector.h"

#import "ALScanResult.h"
#import "ALScanInfo.h"
#import "ALRunSkippedReason.h"

#import "ALScanView.h"
#import "ALCutoutView.h"

@protocol AnylineDebugDelegate;

/**
 * The AnylineAbstractModuleView is a programmatic interface for an object that manages easy access to Anylines scanning modes.  It is a subclass of UIView.
 * You should sublcass this class to build Anyline modules.
 *
 * Overwrite startScanningAndReturnError: to add additional initilization before scanning begins.
 *
 * Overwrite cancelScanningAndReturnError: to do additional clean-up after scanning ends.
 *
 * Overwrite reportScanResultState: to check the various scanning states
 *
 */
__attribute__((deprecated("As of release 10.1, use an ALAbstractViewPlugin instead. This class will be removed by November 2019.")))
@interface AnylineAbstractModuleView : UIView

@property (nullable, nonatomic, weak) id<AnylineDebugDelegate> debugDelegate;

/**
 The video view which is responsible for video preview, frame extraction, ...
 */
@property (nullable, nonatomic, strong) ALScanView *cameraView;

@property (nullable, nonatomic, strong, readonly) ALCaptureDeviceManager *captureDeviceManager;

@property (nullable, nonatomic, strong) ALCutoutView *cutoutView;

@property (nullable, nonatomic, strong) ALFlashButton *flashButton;

@property (nullable, nonatomic, strong) ALTorchManager *torchManager;

/**
 * The UI Configuration for the scanning UI
 */
@property (nullable, nonatomic, copy) ALUIConfiguration *currentConfiguration;


/**
 *  Sets the width of the views border
 */
@property (nonatomic) IBInspectable NSInteger strokeWidth;

/**
 *  Sets the color of the views border
 */
@property (nullable, nonatomic, strong) IBInspectable UIColor *strokeColor;

/**
 *  Sets the corner radius of the views border
 */
@property (nonatomic) IBInspectable NSInteger cornerRadius;

/**
 *  Sets the color of the space surrounding the view
 */
@property (nullable, nonatomic, strong) IBInspectable UIColor *outerColor;

/**
 *  Sets the alpha of the space surrounding the view
 */
@property (nonatomic) IBInspectable CGFloat outerAlpha;

/**
 *  Sets image the user uses to toggle the flash
 */
@property (nullable, nonatomic, strong) IBInspectable UIImage *flashImage;

/**
 *  Sets the alignment of the flash button. Possible values are:
 *  ALFlashAlignmentTop, ALFlashAlignmentTopLeft, ALFlashAlignmentTopRight,
 *  ALFlashAlignmentBottomLeft, ALFlashAlignmentBottom and
 *  ALFlashAlignmentBottomRight
 */
@property (nonatomic) ALFlashAlignment flashButtonAlignment;

/**
 * Property for the flash button offset.
 */
@property (nonatomic) CGPoint flashButtonOffset;

/**
 *  Reads the status of the flash
 */
@property (nonatomic) ALFlashStatus flashStatus;

/**
 *  This property tells Anyline if it should stop reading once a result was found
 */
@property (nonatomic) IBInspectable BOOL cancelOnResult;

/**
 *  This property tells Anyline if it should beep once a result was found
 */
@property (nonatomic) IBInspectable BOOL beepOnResult;

/**
 *  This property tells Anyline if it should blink once a result was found
 */
@property (nonatomic) IBInspectable BOOL blinkOnResult;

/**
 *  This property tells Anyline if it should vibrate once a result was found
 */
@property (nonatomic) IBInspectable BOOL vibrateOnResult;

/**
 * Returns the bounding Rect of the visible Cutout with the correct location on the Module View.
 *
 * @warning May be nil before the layout process is completed.
 */
@property (nonatomic, readonly) CGRect cutoutRect;

/**
 * Returns the bounding Rect of the visible WatermarkView with the correct location on the Module View.
 *
 * @warning May be nil before the layout process is completed or the license is not community.
 */
@property (nonatomic, readonly) CGRect watermarkRect;

/**
 *  Starts the scanning process or sets the error object
 *
 *  @param error The error that occured
 *
 *  @return Boolean indicating if the scanning could be started
 */
- (BOOL)startScanningAndReturnError:(NSError * _Nullable * _Nullable )error;

/**
 *  Stops the scanning process or sets the error object
 *
 *  @param error The error that occured
 *
 *  @return Boolean indicating if the scanning could be stopped
 */
- (BOOL)cancelScanningAndReturnError:(NSError * _Nullable * _Nullable )error;

/**
 * Reporting ON Switch, off by default
 *
 * @param enable if YES, anyline will report for QA failed scan tries. Use reportImageForLog in ALC file,
 *               and use the reportScanResultState: for reporting
 */
-(void)enableReporting:(BOOL)enable;

/**
 * @return Boolean indicating if a scanning is in progress.
 */
- (BOOL)isRunning;

/**
 * Stop listening for device motion.
 */
- (void)stopListeningForMotion;

@end

/**
 *  The delegate for the AnylineOCRModuleView.
 */
__attribute__((deprecated("As of release 10.1, use an ALInfoDelegate with an ALAbstractScanPlugin instead. This class will be removed by November 2019.")))
@protocol AnylineDebugDelegate <NSObject>

@optional
/**
 * <p>Called with interesting values, that arise during processing.</p>
 * <p>
 * Some possibly reported values:
 * <ul>
 * <li>$brightness - the brightness of the center region of the cutout as a float value </li>
 * <li>$confidence - the confidence, an Integer value between 0 and 100 </li>
 * <li>$thresholdedImage - the current image transformed into black and white (the base image used for OCR)</li>
 * </ul>
 * </p>
 *
 *  @param anylineModuleView The AnylineAbstractModuleView
 *  @param variableName         The variable name of the reported value
 *  @param value                The reported value
 */
- (void)anylineModuleView:(AnylineAbstractModuleView * _Nonnull)anylineModuleView
      reportDebugVariable:(NSString * _Nonnull)variableName
                    value:(id _Nonnull)value;
/**
 *  Is called when the processing is aborted for the current image before reaching return.
 *  (If not text is found or confidence is to low, etc.)
 *
 *  @param anylineModuleView The AnylineAbstractModuleView
 *  @param runFailure        The reason why the run failed
 */
- (void)anylineModuleView:(AnylineAbstractModuleView * _Nonnull)anylineModuleView
               runSkipped:(ALRunFailure)runFailure;

@end
