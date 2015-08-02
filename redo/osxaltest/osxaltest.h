// 31 july 2015
#import <Cocoa/Cocoa.h>
#import <stdint.h>

@protocol tControl
@required
- (void)tSetParent:(id<tControl>)p addToView:(NSView *)v;
- (void)tFillAutoLayoutHorz:(NSMutableArray *)horz
	vert:(NSMutableArray *)vert
	extra:(NSMutableArray *)extra
	extraVert:(NSMutableArray *)extraVert
	views:(NSMutableDictionary *)views
	first:(uintmax_t *)n;
- (void)tRelayout;
@end

@interface tWindow : NSObject<tControl>
- (void)tSetControl:(id<tControl>)cc;
- (void)tSetMargined:(BOOL)m;
- (void)tShow;
@end

@interface tBox : NSObject<tControl>
- (id)tInitVertical:(BOOL)vert;
- (void)tAddControl:(id<tControl>)c stretchy:(BOOL)s;
@end

@interface tButton : NSObject<tControl>
- (id)tInitWithText:(NSString *)text;
@end

@interface tSpinbox : NSObject<tControl>
@end

extern NSString *tAutoLayoutKey(uintmax_t);