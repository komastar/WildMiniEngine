//
//  ViewImpl.h
//  WMFramework
//
//  Created by Eugene Kim on 2023/05/01.
//

#ifdef __APPLE__
#ifndef ViewImpl_h
#define ViewImpl_h
#import <AppKit/AppKit.h>

@interface ViewImpl : NSView<NSTextInputClient, NSWindowDelegate, NSDraggingDestination>
{

}
@end

#endif /* ViewImpl_h */
#endif /* __APPLE__ */
