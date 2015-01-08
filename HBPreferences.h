/**
 * The `HBPreferences` class in `libcephei` provides an interface for managing
 * user-defined preferences of a tweak, and the default values used when the
 * user has not yet changed a value.
 *
 * `HBPreferences` is very similar to `NSUserDefaults`, however it is
 * specifically tailored to iOS tweak development, since tweaks may be loaded
 * into a sandboxed app (for instance, App Store apps), or one that runs as
 * the `root` user (for instance, Cydia). In both of these cases, using
 * `NSUserDefaults` will result in reading from preferences inside the
 * sandbox, or inside `root`'s home directory; both of which are not what is
 * expected.
 *
 * Advantages `HBPreferences` has over `NSUserDefaults` are:
 *
 * - Directly reading the property list from the `mobile` user's home
 * directory, to support sandboxed apps and apps running as `root`.
 * - Intuitive method of setting a default preference value.
 * - Updating of the app/tweak's variables when preferences are changed.
 * - Keyed subscripting is allowed, which enables simple array syntax.
 * - Values in the preferences plist are called preferences, not defaults, to
 * avoid ambiguity - `NSUserDefaults` uses "defaults" to refer to both
 * preferences themselves and the defaults if a key doesn't exist.
 *
 * ### Example usage:
 *
 * 	BOOL doThing;
 *
 * 	%ctor {
 * 		preferences = [[HBPreferences alloc] initWithIdentifier:@"ws.hbang.common.demo"];
 * 		[preferences registerDefaults:@{
 * 			@"Enabled": @YES,
 * 			@"AnotherSetting": @1.f
 * 		}];
 *
 * 		[preferences registerBool:&doThing default:NO forKey:@"DoThing"];
 *
 * 		NSLog(@"Am I enabled? %i", [preferences boolForKey:@"Enabled"]);
 * 		NSLog(@"Can I do thing? %i", doThing);
 * 	}
 */

@interface HBPreferences : NSObject

/**
 * @name Initializing an HBPreferences Object
 */

/**
 * Creates an instance of the class for the specified identifier.
 *
 * @param identifier The identifier to be used. This is usually the same as the
 * package identifier of the tweak.
 * @returns An autoreleased instance of HBPreferences for the specified identifier.
 */
+ (instancetype)preferencesForIdentifier:(NSString *)identifier;

/**
 * Initializes an instance of the class for the specified identifier.
 *
 * @param identifier The identifier to be used. This is usually the same as the
 * package identifier of the tweak.
 * @returns An autoreleased instance of HBPreferences for the specified identifier.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier;

/**
 * The preferences identifier provided at initialisation.
 */
@property (nonatomic, retain, readonly) NSString *identifier;

/**
 * @name Getting Preference Values
 */

/**
 * Returns the object associated with the specified key.
 *
 * If the preference is not yet set, returns the default. If no default is set,
 * returns `nil`.
 *
 * @param key The key for which to return the corresponding value.
 * @returns The object associated with the specified key.
 */
- (id)objectForKey:(NSString *)key;

/**
 * Returns the integer value associated with the specified key.
 *
 * If the preference is not yet set, returns the default. If no default is set,
 * returns `nil`.
 *
 * @param key The key for which to return the corresponding value.
 * @returns The integer value associated with the specified key.
 */
- (NSInteger)integerForKey:(NSString *)key;

/**
 * Returns the floating-point value associated with the specified key.
 *
 * If the preference is not yet set, returns the default. If no default is set,
 * returns `nil`.
 *
 * @param key The key for which to return the corresponding value.
 * @returns The floating-point value associated with the specified key.
 */
- (CGFloat)floatForKey:(NSString *)key;

/**
 * Returns the double value associated with the specified key.
 *
 * If the preference is not yet set, returns the default. If no default is set,
 * returns `nil`.
 *
 * @param key The key for which to return the corresponding value.
 * @returns The double value associated with the specified key.
 */
- (double)doubleForKey:(NSString *)key;

/**
 * Returns the Boolean value associated with the specified key.
 *
 * If the preference is not yet set, returns the default. If no default is set,
 * returns `nil`.
 *
 * @param key The key for which to return the corresponding value.
 * @returns The Boolean value associated with the specified key.
 */
- (BOOL)boolForKey:(NSString *)key;

/**
 * Returns the value associated with a given key.
 *
 * This method behaves the same as objectForKey:.
 *
 * @param key The key for which to return the corresponding value.
 * @returns The value associated with the specified key.
 */
- (id)objectForKeyedSubscript:(id)key;

/**
 * Returns the object associated with the specified key, or if no
 * user preference is set, the provided default.
 *
 * @param key The key for which to return the corresponding value.
 * @param defaultValue The default value to use when no user preference is set.
 * @returns The object associated with the specified key, or the default value.
 */
- (id)objectForKey:(NSString *)key default:(id)defaultValue;

/**
 * Returns the integer value associated with the specified key, or if no
 * user preference is set, the provided default.
 *
 * @param key The key for which to return the corresponding value.
 * @param defaultValue The default value to use when no user preference is set.
 * @returns The integer value associated with the specified key, or the default
 * value.
 */
- (NSInteger)integerForKey:(NSString *)key default:(NSInteger)defaultValue;

/**
 * Returns the floating-point value associated with the specified key, or if no
 * user preference is set, the provided default.
 *
 * @param key The key for which to return the corresponding value.
 * @param defaultValue The default value to use when no user preference is set.
 * @returns The floating-point value associated with the specified key, or the
 * default value.
 */
- (CGFloat)floatForKey:(NSString *)key default:(CGFloat)defaultValue;

/**
 * Returns the double value associated with the specified key, or if no
 * user preference is set, the provided default.
 *
 * @param key The key for which to return the corresponding value.
 * @param defaultValue The default value to use when no user preference is set.
 * @returns The double value associated with the specified key, or the default
 * value.
 */
- (double)doubleForKey:(NSString *)key default:(double)defaultValue;

/**
 * Returns the Boolean value associated with the specified key, or if no
 * user preference is set, the provided default.
 *
 * @param key The key for which to return the corresponding value.
 * @param defaultValue The default value to use when no user preference is set.
 * @returns The Boolean value associated with the specified key, or the default
 * value.
 */
- (BOOL)boolForKey:(NSString *)key default:(BOOL)defaultValue;

/**
 * @name Setting Preference Values
 */

/**
 * Sets the value of the specified key.
 *
 * You should only call these methods if you are certain that the process is
 * running as the `mobile` user.
 *
 * @param value The object to store in the preferences.
 * @param key The key with which to associate with the value.
 * @exception HBPreferencesNotMobileException Thrown when the method is called
 * by a user other than `mobile`.
 */
- (void)setObject:(id)value forKey:(NSString *)key;

/**
 * Sets the value of the specified key to the specified integer value.
 *
 * This is a convenience method that calls setObject:forKey:. See the discussion
 * of that method for more details.
 *
 * @param value The integer value to store in the preferences.
 * @param key The key with which to associate with the value.
 */
- (void)setInteger:(NSInteger)value forKey:(NSString *)key;

/**
 * Sets the value of the specified key to the specified floating-point value.
 *
 * This is a convenience method that calls setObject:forKey:. See the discussion
 * of that method for more details.
 *
 * @param value The floating-point value to store in the preferences.
 * @param key The key with which to associate with the value.
 */
- (void)setFloat:(CGFloat)value forKey:(NSString *)key;

/**
 * Sets the value of the specified key to the specified double value.
 *
 * This is a convenience method that calls setObject:forKey:. See the discussion
 * of that method for more details.
 *
 * @param value The double value to store in the preferences.
 * @param key The key with which to associate with the value.
 */
- (void)setDouble:(double)value forKey:(NSString *)key;

/**
 * Sets the value of the specified key to the specified Boolean value.
 *
 * This is a convenience method that calls setObject:forKey:. See the discussion
 * of that method for more details.
 *
 * @param value The Boolean value to store in the preferences.
 * @param key The key with which to associate with the value.
 */
- (void)setBool:(BOOL)value forKey:(NSString *)key;

/**
 * Sets the value of the specified key to the specified value.
 *
 * @param object The value to store in the preferences.
 * @param key The key with which to associate with the value.
 */
- (void)setObject:(id)object forKeyedSubscript:(id)key;

/**
 * @name Registering Default Preferences
 */

/**
 * The default preferences to be used when no value has been set by the user.
 *
 * You may modify the values of this dictionary directly.
 */
@property (nonatomic, retain, readonly) NSMutableDictionary *defaults;

/**
 * Register an object to be automatically set to the user's preference.
 *
 * If the preference is not yet set, the object will be set to the provided
 * default.
 *
 * @param object The pointer to the object.
 * @param defaultValue The default value to be used if no user preference is set.
 * @param key The key in the preferences property list.
 */
- (void)registerObject:(void *)object default:(id)defaultValue forKey:(NSString *)key;

/**
 * Register an integer value to be automatically set to the user's preference.
 *
 * If the preference is not yet set, the object will be set to the provided
 * default.
 *
 * @param object The pointer to the integer.
 * @param defaultValue The default value to be used if no user preference is set.
 * @param key The key in the preferences property list.
 */
- (void)registerInteger:(NSInteger *)object default:(NSInteger)defaultValue forKey:(NSString *)key;

/**
 * Register a floating-point value to be automatically set to the user's
 * preference.
 *
 * If the preference is not yet set, the object will be set to the provided
 * default.
 *
 * @param object The pointer to the integer.
 * @param defaultValue The default value to be used if no user preference is set.
 * @param key The key in the preferences property list.
 */
- (void)registerFloat:(CGFloat *)object default:(CGFloat)defaultValue forKey:(NSString *)key;

/**
 * Register a double value to be automatically set to the user's preference.
 *
 * If the preference is not yet set, the object will be set to the provided
 * default.
 *
 * @param object The pointer to the double.
 * @param defaultValue The default value to be used if no user preference is set.
 * @param key The key in the preferences property list.
 */
- (void)registerDouble:(double *)object default:(double)defaultValue forKey:(NSString *)key;

/**
 * Register a Boolean value to be automatically set to the user's preference.
 *
 * If the preference is not yet set, the object will be set to the provided
 * default.
 *
 * @param object The pointer to the Boolean.
 * @param defaultValue The default value to be used if no user preference is set.
 * @param key The key in the preferences property list.
 */
- (void)registerBool:(BOOL *)object default:(BOOL)defaultValue forKey:(NSString *)key;

/*
 * Adds the contents of the specified dictionary to the defaults property.
 *
 * Provided as a convenience for converting code from using `NSUserDefaults`.
 *
 * @param defaultValues The dictionary of keys and values you want to register.
 */
- (void)registerDefaults:(NSDictionary *)defaultValues;

/*
 * @name Synchronizing Preferences
 */

/*
 * Writes all pending changes to preference data to permanent storage, and
 * reads latest preference data from permanent storage.
 *
 * Do not use this function directly unless you have a specific need.
 * Synchronization is automatically invoked at periodic intervals. Use this
 * method if you cannot wait for automatic synchronization (for example, if the
 * process is about to exit).
 *
 * @returns `YES` if synchronization was successful, `NO` if an error occurred.
 */
- (BOOL)synchronize;

@end

#ifndef _HB_PREFERENCES_M
/**
 * Name of an exception that occurs when attempting to set preferences from a
 * process not running as the `mobile` user.
 */
extern NSString *const HBPreferencesNotMobileException;

/**
 * This notification is posted when a change is made to a registered
 * preferences identifier. The notification object is the associated
 * HBPreferences object.
 */
extern NSString *const HBPreferencesDidChangeNotification;
#endif
