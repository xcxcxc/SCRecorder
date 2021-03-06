//
//  SCVideoPlayer.h
//  SCAudioVideoRecorder
//
//  Created by Simon CORSIN on 8/30/13.
//  Copyright (c) 2013 rFlex. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "SCImageView.h"
#import "CIImageRenderer.h"

@class SCPlayer;

@protocol SCPlayerDelegate <NSObject>

@optional

/**
 Called when the player has played some frames. The loopsCount will contains the number of 
 loop if the curent item was set using setSmoothItem.
 */
- (void)player:(SCPlayer*)player didPlay:(CMTime)currentTime loopsCount:(NSInteger)loopsCount;

/**
 Called when the item has been changed on the SCPlayer
 */
- (void)player:(SCPlayer *)player didChangeItem:(AVPlayerItem*)item;

/**
 Called when the item has reached end
 */
- (void)player:(SCPlayer *)player didReachEndForItem:(AVPlayerItem *)item;

/**
 Called when the item is ready to play
 */
- (void)player:(SCPlayer *)player itemReadyToPlay:(AVPlayerItem *)item;

@end

/**
 A player that inherits from the standard AVPlayer but adds some feature, such as the
 CIImageRenderer support.
 */
@interface SCPlayer : AVPlayer

/**
 The delegate that will receive the messages
 */
@property (weak, nonatomic) id<SCPlayerDelegate> delegate;

/**
 Whether the video should start again from the beginning when its reaches the end
 */
@property (assign, nonatomic) BOOL loopEnabled;

/**
 Will be true if beginSendingPlayMessages has been called.
 */
@property (readonly, nonatomic) BOOL isSendingPlayMessages;

/**
 Whether this instance is currently playing.
 */
@property (readonly, nonatomic) BOOL isPlaying;

/**
 The actual item duration.
 */
@property (readonly, nonatomic) CMTime itemDuration;

/**
 The total currently loaded and playable time.
 */
@property (readonly, nonatomic) CMTime playableDuration;

/**
 If true, the player will figure out an affine transform so the video best fits the screen. The resulting video may not be in the correct device orientation though.
 For example, if the video is in landscape and the current device orientation is in portrait mode,
 with this property enabled the video will be rotated so it fits the entire screen. This avoid
 showing the black border on the sides. If your app supports multiple orientation, you typically
 wouldn't want this feature on.
 */
@property (assign, nonatomic) BOOL autoRotate;

/**
 The renderer for the CIImage. If this property is set, the player will set the CIImage
 property when the current frame changes.
 */
@property (strong, nonatomic) id<CIImageRenderer> CIImageRenderer;

/**
 Convenient method to return a new instance of a SCPlayer
 */
+ (SCPlayer *)player;

/**
 Ask the SCPlayer to send didPlay messages during the playback
 endSendingPlayMessages must be called, otherwise the SCPlayer will never
 be deallocated
 */
- (void)beginSendingPlayMessages;

/**
 Ask the SCPlayer to stop sending didPlay messages during the playback
 */
- (void)endSendingPlayMessages;

/**
 Set the item using a file string path.
 */
- (void)setItemByStringPath:(NSString*)stringPath;

/**
 Set the item using an URL
 */
- (void)setItemByUrl:(NSURL*)url;

/**
 Set the item using an Asset
 */
- (void)setItemByAsset:(AVAsset*)asset;

/**
 Set the item using an AVPlayerItem
 */
- (void)setItem:(AVPlayerItem*)item;

/**
 Set an item using a file string path. This will generate an AVComposition containing "loopCount"
 times the item. This avoids the hiccup when looping for up to "loopCount" times.
 */
- (void)setSmoothLoopItemByStringPath:(NSString*)stringPath smoothLoopCount:(NSUInteger)loopCount;

/**
 Set the item using an URL. This will generate an AVComposition containing "loopCount"
 times the item. This avoids the hiccup when looping for up to "loopCount" times.
 */
- (void)setSmoothLoopItemByUrl:(NSURL*)url smoothLoopCount:(NSUInteger)loopCount;

/**
 Set the item using an Asset. This will generate an AVComposition containing "loopCount"
 times the item. This avoids the hiccup when looping for up to "loopCount" times.
 */
- (void)setSmoothLoopItemByAsset:(AVAsset*)asset smoothLoopCount:(NSUInteger)loopCount;


@end
