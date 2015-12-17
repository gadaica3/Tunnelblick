/*
 * Copyright 2010, 2011, 2012, 2013, 2014, 2015 Jonathan K. Bullard. All rights reserved.
 *
 *  This file is part of Tunnelblick.
 *
 *  Tunnelblick is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 *
 *  Tunnelblick is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program (see the file COPYING included with this
 *  distribution); if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  or see http://www.gnu.org/licenses/.
 */


/*  ConfigurationManager
 *
 *  This class manipulates configurations (.ovpn and .conf files and .tblk packages)
 *
 *  It takes care of protecting and unprotecting configurations and making shadow copies of them,
 *  and installing .tblk packages
 */

#import "defines.h"

@class ListingWindowController;
@class VPNConnection;

@interface ConfigurationManager : NSObject {
	
	ListingWindowController * listingWindow;

    // The following variables are used by installConfigurations:skipConfirmationMessage:skipResultMessage:NotifyDelegate: and the methods it invokes:
   
    NSString * applyToAllSharedPrivate;
    NSString * applyToAllUninstall;
    NSString * applyToAllReplaceSkip;
    
    NSString * tempDirPath;
    
    NSMutableString * errorLog;
    
    NSMutableArray * installSources;	// Paths of .tblks to copy to install
    NSMutableArray * installTargets;
	NSMutableArray * replaceSources;	// Paths of .tblks to copy to replace
	NSMutableArray * replaceTargets;
    NSMutableArray * noAdminSources;	// Paths of .tblks in which keys and certs (only) are to be updated without admin credentials
    NSMutableArray * noAdminTargets;
	NSMutableArray * updateSources;		// Paths of .tblk stubs to copy to L_AS_T_TBLKS for updatable configurations
	NSMutableArray * updateTargets;
    NSMutableArray * deletions;			// Paths of .tblks to delete to uninstall
	
    BOOL inhibitCheckbox;
    BOOL installToSharedOK;
    BOOL installToPrivateOK;
    BOOL authWasNull;
	BOOL multipleConfigurations;
}

+(NSDictionary *)           plistInTblkAtPath:          (NSString *)         path;

+(void)                     editOrExamineConfigurationForConnection: (VPNConnection *) connection;

+(NSMutableDictionary *)    getConfigurations;

+(NSString *)               parseConfigurationPath:     (NSString *)        cfgPath
                                     forConnection:     (VPNConnection *)   connection
                                   hasAuthUserPass:     (BOOL *)            hasAuthUserPass;

+(BOOL)                     userCanEditConfiguration:   (NSString *)        filePath;

+(void) makeConfigurationsPrivateInNewThreadWithDisplayNames: (NSArray *) displayNames;

+(void) makeConfigurationsSharedInNewThreadWithDisplayNames: (NSArray *) displayNames;

+(void) removeConfigurationsInNewThreadWithDisplayNames: (NSArray *) displayNames;

+(void) revertToShadowInNewThreadWithDisplayNames: (NSArray *) displayNames;

+(void) removeCredentialsInNewThreadWithDisplayNames: (NSArray *) displayNames;

+(void) removeCredentialsGroupInNewThreadWithName: (NSString *) name;

+(void) renameConfigurationInNewThreadWithDisplayName: (NSString *) displayName;

+(void) createShadowConfigurationInNewThreadWithDisplayName: (NSString *) displayName thenConnectUserKnows: (BOOL) userKnows
													;

+(void) renameConfigurationInNewThreadAtPath: (NSString *) sourcePath toPath: (NSString *) targetPath;

+(void) duplicateConfigurationInNewThreadPath: (NSString *) sourcePath toPath: (NSString *) targetPath;

+(void) installConfigurationsUpdateInBundleInNewThreadAtPath: (NSString *) path;

+(void) installConfigurationsInNewThreadShowMessagesNotifyDelegateWithPaths: (NSArray *) filePaths;

+(void) installConfigurationsInNewThreadShowMessagesDoNotNotifyDelegateWithPaths: (NSArray *) filePaths;

+(void) putDiagnosticInfoOnClipboardInNewThreadForDisplayName: (NSString *) displayName;

+(void) killAllOpenVPNInNewThread;

+(void) putConsoleLogOnClipboardInNewThread;

+(void) addConfigurationGuideInNewThread;

+(void) haveNoConfigurationsGuideInNewThread;

+(void) installConfigurationsInCurrentMainThreadDoNotShowMessagesDoNotNotifyDelegateWithPaths: (NSArray *)  paths;

@end
