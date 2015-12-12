//
//  Created by Marco Arment on 2014-04-06.
//  Copyright (c) 2014 Marco Arment. See included LICENSE file.
//

#import "UIView+CompactConstraint.h"

@implementation CCView (CompactConstraint)

- (NSLayoutConstraint *)hb_addCompactConstraint:(NSString *)relationship metrics:(NSDictionary *)metrics views:(NSDictionary *)views
{
    NSLayoutConstraint *constraint = [NSLayoutConstraint hb_compactConstraint:relationship metrics:metrics views:views self:self];
    [self addConstraint:constraint];
    return constraint;
}

- (NSArray *)hb_addCompactConstraints:(NSArray *)relationshipStrings metrics:(NSDictionary *)metrics views:(NSDictionary *)views;
{
    NSMutableArray *mConstraints = [NSMutableArray arrayWithCapacity:relationshipStrings.count];
    for (NSString *relationship in relationshipStrings) {
        if ([relationship hasPrefix:@"H:"] || [relationship hasPrefix:@"V:"] || [relationship hasPrefix:@"|"] || [relationship hasPrefix:@"["]) {
            [mConstraints addObjectsFromArray:[NSLayoutConstraint hb_identifiedConstraintsWithVisualFormat:relationship options:0 metrics:metrics views:views]];
        } else {
            [mConstraints addObject:[NSLayoutConstraint hb_compactConstraint:relationship metrics:metrics views:views self:self]];
        }
    }
    NSArray *constraints = [mConstraints copy];
    [self addConstraints:constraints];
    return constraints;
}

- (void)hb_addConstraintsWithVisualFormat:(NSString *)format options:(NSLayoutFormatOptions)opts metrics:(NSDictionary *)metrics views:(NSDictionary *)views
{
    [self addConstraints:[NSLayoutConstraint hb_identifiedConstraintsWithVisualFormat:format options:opts metrics:metrics views:views]];
}

@end