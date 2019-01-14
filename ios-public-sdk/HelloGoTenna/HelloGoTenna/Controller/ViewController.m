//
//  ViewController.m
//  HelloGoTenna
//
//  Created by GoTenna on 7/20/18.
//  Copyright © 2018 goTenna. All rights reserved.
//

#import "ViewController.h"
#import "ChatViewController.h"
#import "GroupCreateViewController.h"
#import "ContactManager.h"
#import "MessagingManager.h"
#import "FirmwareManager.h"
#import "DemoConstants.h"
#import "Group.h"
#import "Contact.h"
#import "LocationManager.h"

@import GoTennaSDK;

static NSString * const cellID = @"cellId";

@interface ViewController () <GTPairingHandlerProtocol, BluetoothPairingProtocol, FirmwareManagerProtocol>

@property (nonatomic, weak) IBOutlet UITableView *tableView;
@property (nonatomic, weak) IBOutlet UIBarButtonItem *connectBarItem;

@property (nonatomic, strong) FirmwareManager *firmwareManager;
@property (nonatomic, strong) NSString *firmwareUpdateStatus;
@property (nonatomic, strong) Group *selectedGroup;

@property (nonatomic, strong) NSString *oldStateString;
//@property (nonatomic, strong) GTMeshGeofence *geofence;
//@property (nonatomic, strong) LocationManager *locationManager;
#warning Uncomment the references to GTMeshGeoFence & LocationManager for Mesh frequency setting
@end

@implementation ViewController

//MARK:- actions

- (IBAction)connect:(id)sender {
    
    BOOL isConnected = [[BluetoothConnectionManager shared] isConnected];
    
    if (isConnected) {
        [self disconnectFromGoTenna];
    } else {
        [self scanForNewGoTenna];
    }
}

- (void)scanForNewGoTenna {
    [[GTPairingManager shared] setShouldReconnect:YES];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:[GTConfig forgetThisDeviceKey]];
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"GoTenna"
                                                                   message:@"Select a device to scan for."
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *pro = [UIAlertAction actionWithTitle:@"goTenna Pro X" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [[BluetoothConnectionManager shared] setDevice:GTDeviceTypePro];
        [[GTPairingManager shared] initiateScanningConnect];
        [self.connectBarItem setTitle:@"Connecting"];
    }];
    
    UIAlertAction *mesh = [UIAlertAction actionWithTitle:@"goTenna Mesh" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [[BluetoothConnectionManager shared] setDevice:GTDeviceTypeMesh];
        [[GTPairingManager shared] initiateScanningConnect];
        [self.connectBarItem setTitle:@"Connecting"];
    }];
    
    [alert addAction:pro];
    [alert addAction:mesh];
    
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)disconnectFromGoTenna {
    [[GTPairingManager shared] setShouldReconnect:NO];
    [[GTPairingManager shared] initiateDisconnect];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:[GTConfig forgetThisDeviceKey]];
    [self.connectBarItem setTitle:@"Connect"];
}

- (void)chooseDemoUser {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Set Name & GID"
                                                                   message:@"Select a demo user"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    for (Contact *contact in [[ContactManager sharedManager] allDemoContacts]) {
        NSString *title = [NSString stringWithFormat:@"%@ (%@)", contact.name, contact.gid.stringValue];
        
        UIAlertAction *action = [UIAlertAction actionWithTitle:title style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            [self sendSetGID:contact.gid name:contact.name withBlock:^(BOOL success) {
                if (success) {
                    self.connectBarItem.enabled = YES;
                    self.tableView.userInteractionEnabled = YES;
                    
                    [self reloadSection:0];
                }
            }];
        }];
        
        [alert addAction:action];
    }
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        // nothing
    }];
    [alert addAction:cancel];
    
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)chooseGroup {
    
    if ([[[ContactManager sharedManager] allGroups] count] == 0) {
        
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Error"
                                                                       message:@"You must be invited by another demo user to send a group message or create a group yourself."
                                                                preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
            // nothing
        }];
        
        [alert addAction:cancel];
        
        [self presentViewController:alert animated:YES completion:nil];
        return;
    }
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Group"
                                                                   message:@"Select a group"
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    
    
    for (Group *group in [[ContactManager sharedManager] allGroups]) {
        NSString *title = [NSString stringWithFormat:@"%@ (%lu members)", group.groupGID, (unsigned long)group.groupMembers.count];
        
        UIAlertAction *action = [UIAlertAction actionWithTitle:title style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            self.selectedGroup = group;
            [self performSegueWithIdentifier:@"ChatSegue" sender:@(GroupGID)];
        }];
        
        [alert addAction:action];
    }
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
    [alert addAction:cancel];
    
    [self presentViewController:alert animated:YES completion:nil];
}

//MARK:- device actions

- (void)sendEchoWithBlock:(void (^)(BOOL success))block {
    [[GTCommandCenter shared] sendEchoCommand:^(GTResponse *response) {
        block(response.responsePositive);
    } onError:^(NSError *error) {
        NSLog(@"[GoTenna] Error %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
        block(NO);
    }];
}

- (void)sendGetSystemInfoWithBlock:(void (^)(NSString *systemInfoDescription))block {
    [[GTCommandCenter shared] sendGetSystemInfoOnSuccess:^(SystemInfoResponseData *response) {
        block([response asString]);
    } onError:^(NSError *error) {
        NSLog(@"[GoTenna] Error %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
        block(nil);
    }];
}

- (void)sendSetGID:(NSNumber *)gid name:(NSString *)name withBlock:(void (^)(BOOL success))block {
    [[GTCommandCenter shared] setgoTennaGID:gid withUsername:name onError:^(NSError *error) {
        if (error) {
            NSLog(@"[GoTenna] Error %@ %@", NSStringFromSelector(_cmd), error.localizedDescription);
            block(NO);
        }
    }];
    
    block(YES);
}

//MARK:- pairing handler protocol

- (void)updateState:(GTConnectionState)state {
    switch (state) {
        case Disconnected:
            [self.connectBarItem setTitle:@"Connect"];
            [self.connectBarItem setEnabled:YES];
            break;
        case Connecting:
            [self.connectBarItem setTitle:@"Connecting"];
            [self.connectBarItem setEnabled:NO];
            break;
        case Connected:
            [self.connectBarItem setTitle:@"Disconnect"];
            [self.connectBarItem setEnabled:YES];
            
            if (![[UserDataStore shared] currentUser]) {
                [self chooseDemoUser];
            } else {
                // Ensure GID has been set to current device
                if ([[UserDataStore shared] currentUser]) {
                    [self sendSetGID:[[UserDataStore shared] currentUser].gId name:[[UserDataStore shared] currentUser].name withBlock:^(BOOL success) {
                        if (!success) {
                            [self showAlertWithTitle:@"Error" message:@"Failed to send set GID command."];
                        }
                    }];
                }
            }

            if ([BluetoothConnectionManager shared].isProDevice) {
                
                GTFrequencyData *frequencyData = [self createExampleFrequencySlot];
                [[GTFrequencySync sharedInstance] setOnSyncSuccess:^{
                    NSLog(@"Successfully sent frequency values to firmware");
                }];
                
                [[GTFrequencySync sharedInstance] setOnSyncFailed:^(NSError *error) {
                    NSLog(@"Failed to send frequency values to firmware. Error: %@",error);
                }];
                
                [[GTFrequencySync sharedInstance] syncFrequencySettingsWithSlot:frequencyData];
            }
            else if ([BluetoothConnectionManager shared].isMeshDevice) {
                /*[self.locationManager retrieveMyLocation:^(CLLocation *myLocation) {
                    // Send up location once we have our current location
                    [self.geofence regionIDForLocation:myLocation.coordinate
                                      regionIDResponse:^(RegionID regionID, BOOL regionFound) {
                                          if ([[BluetoothConnectionManager shared] isConnected]) {
                                              [[GTCommandCenter shared] sendSetGeoRegion:regionID onResponse:^(GTResponse *res) {
                                                  dispatch_async(dispatch_get_main_queue(), ^{
                                                      NSLog(@"RegionID (%@) %@ on goTenna for region %@",@(regionID),(res.responsePositive ? @"set" : @"not set"),[RegionBound regionNameFromId:regionID]);
                                                  });
                                              } onError:^(NSError *err) {
                                                  dispatch_async(dispatch_get_main_queue(), ^{
                                                      NSLog(@"Set Region Error: %@",err);
                                                  });
                                              }];
                                          }
                                      }];
                }];*/
            }
            break;
    }
}

//MARK:- firmware protocol

- (void)firmwareManager:(FirmwareManager *)firmwareManager didUpdateState:(FirmwareUpdateState)state progress:(float)progress {
    NSString *stateString = nil;
    
    switch (state) {
        case UpdateInitialized:
            stateString = @"Initialized";
            break;
        case UpdateInitializeComplete:
            stateString = @"Initialize complete";
            break;
        case UpdateProgressChanged:
            stateString = [NSString stringWithFormat:@"%d%%", (int)(progress * 100)];
            break;
        case UpdateFinalizeComplete:
            stateString = @"Finalize complete";
            break;
        case UpdateSucceeded:
            stateString = @"Succeeded";
            break;
        case UpdateFailed:
            stateString = @"Failed";
            break;
    }
    self.firmwareUpdateStatus = stateString;
    
    // prevent flickering
    if (![stateString isEqualToString:self.oldStateString]) {
        [self reloadSection:3];
    }

    self.oldStateString = stateString;
}

//MARK:- bluetooth protocol

- (void)bluetoothPoweredOn {
    // Bluetooth enabled
}

- (void)didConnectToPeripheral {
    // Connected to device
}

- (void)canNotConnectToPeripheral {
    // Could not connect to device
    [self showAlertWithTitle:@"GoTenna" message:@"Could not connect to your device."];
}

- (void)bluetoothConnectionNotAvailable:(CBManagerState)state {
    // Bluetooth is off
    [self showAlertWithTitle:@"GoTenna" message:@"Enable Bluetooth to scan for a device."];
}

- (void)nonUserDisconnectionOccurred {
    // Device disconnected
    [self showAlertWithTitle:@"GoTenna" message:@"Your device was disconnected."];
}

//MARK:- tableview delegate/datasource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 4;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSUInteger rows = 0;
    
    if (section == 0) {
        rows = 2;
    } else if (section == 1) {
        rows = 3;
    } else if (section == 2) {
        rows = 4;
    } else {
        rows = 1;
    }
    
    return rows;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *title = nil;
    
    if (section == 0) {
        title = @"You";
    } else if (section == 1) {
        title = @"Device";
    } else if (section == 2) {
        title = @"Messaging";
    } else {
        title = @"Firmware";
    }
    
    return title;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID forIndexPath:indexPath];
    return [self configureCell:cell forIndexPath:indexPath];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if ([self checkAndShowConnection]) {
        [self handleActionForIndexPath:indexPath];
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

//MARK:- helpers

- (UITableViewCell *)configureCell:(UITableViewCell *)cell forIndexPath:(NSIndexPath *)indexPath {
    NSString *key = nil, *value = nil;
    
    // Name & GID
    if (indexPath.section == 0) {
        switch (indexPath.row) {
            case 0:
                key = @"Name";
                value = [[UserDataStore shared] currentUser].name ?: @"None";
                break;
            case 1:
                key = @"GID";
                value = [NSString presentGID:[[UserDataStore shared] currentUser].gId] ?: @"None";
                break;
        }
    }
    
    // Send Echo, Set System Info, Set GID
    else if (indexPath.section == 1) {
        switch (indexPath.row) {
            case 0:
                key = @"Send Echo";
                break;
            case 1:
                key = @"Send Get System Info";
                break;
            case 2:
                key = @"Set GID";
                break;
        }
    }
    
    // Send Private, Broadcast, Group Messages
    else if (indexPath.section == 2) {
        switch (indexPath.row) {
            case 0:
                key = @"Send Broadcast Message";
                break;
            case 1:
                key = @"Send Private Message";
                break;
            case 2:
                key = @"Create Group";
                break;
            case 3:
                key = @"Send Group Message";
                break;
        }
    }
    // Update Firmware
    else {
        switch (indexPath.row) {
            case 0:
                key = @"Update Firmware";
                value = self.firmwareUpdateStatus;
                break;
        }
    }
    
    cell.textLabel.text = key;
    cell.detailTextLabel.text = value;
    
    cell.accessoryType  = (value) ? UITableViewCellAccessoryNone : UITableViewCellAccessoryDisclosureIndicator;
    cell.selectionStyle = (value) ? UITableViewCellSelectionStyleNone : UITableViewCellSelectionStyleDefault;
    
    return cell;
}

- (void)handleActionForIndexPath:(NSIndexPath *)indexPath {
    // Device
    if (indexPath.section == 1) {
        if (indexPath.row == 0) {
            [self sendEchoWithBlock:^(BOOL success) {
                // ...
            }];
        }
        else if (indexPath.row == 1) {
            [self sendGetSystemInfoWithBlock:^(NSString *systemInfoDescription) {
                [self showAlertWithTitle:@"System Info" message:systemInfoDescription];
            }];
        } else {
            [self chooseDemoUser];
        }
    }
    
    // Messaging
    else if (indexPath.section == 2) {
        GTGIDType conversationType = ShoutGID;
        
        if (![[UserDataStore shared] currentUser]) {
            [self chooseDemoUser];
        } else {
            switch (indexPath.row) {
                case 0:
                    conversationType = ShoutGID;
                    break;
                case 1:
                    conversationType = OneToOneGID;
                    break;
                case 2: {
                    [self performSegueWithIdentifier:@"ToGroupCreate" sender:nil];
                    return;
                }
                    break;
                case 3: {
                    conversationType = GroupGID;
                    [self chooseGroup];
                    return;
                }
                    break;
            }
            
            [self performSegueWithIdentifier:@"ChatSegue" sender:@(conversationType)];

        }        
    }
    // Update Firmware
    else {
        if (indexPath.section == 3 && indexPath.row == 0) {
            [self promptFirmwareUpdate];
        }
    }
}

- (void)reloadSection:(NSUInteger)section {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.tableView beginUpdates];
        [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:section] withRowAnimation:UITableViewRowAnimationAutomatic];
        [self.tableView endUpdates];
    });
}

- (void)handleGroupCreated:(NSNotification *)notification {
    if (notification.name == kGroupCreatedNotification) {
        Group *group = notification.userInfo[kGroupCreatedKey];
        NSString *message = [NSString stringWithFormat:@"You were added to a group of %lu members.", (unsigned long)[group.groupMembers count] - 1];
        
        [self showAlertWithTitle:@"Added to Group" message:message];
    }
}

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *dismiss = [UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleDefault handler:nil];
    
    [alert addAction:dismiss];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)promptFirmwareUpdate {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Firmware update" message:@"Are you sure you'd like to update your device's firmware?" preferredStyle:UIAlertControllerStyleAlert];
    
    __weak typeof(self) weakSelf = self;
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"Begin update" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        weakSelf.firmwareManager = [[FirmwareManager alloc] initWithDelegate:weakSelf];
        
        if (![weakSelf.firmwareManager isUpdatingFirmware]) {
            [weakSelf.firmwareManager beginFirmwareUpdate:^(NSError * error) {
                NSString *errmsg = [NSString stringWithFormat:@"Maybe try using the native app to update the unit's firmware - %@", error.localizedDescription];
                [weakSelf showAlertWithTitle:@"Firmware error" message:errmsg];
            }];
        }
    }];
    
    UIAlertAction *dismiss = [UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleCancel handler:nil];
    
    [alert addAction:confirm];
    [alert addAction:dismiss];
    
    [self presentViewController:alert animated:YES completion:nil];
}

- (BOOL)checkAndShowConnection {
    BluetoothConnectionManager *manager = [BluetoothConnectionManager shared];
    if ([manager isConnected]) {
        return YES;
    } else {
        [self showAlertWithTitle:nil message:@"Connect your goTenna!"];
        return NO;
    }
}

//MARK:- navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"ChatSegue"])  {
        ChatViewController *chatViewController = (ChatViewController *)[segue destinationViewController];
        GTGIDType conversationType = [(NSNumber *)sender intValue];
        
        chatViewController.conversationType = conversationType;
        chatViewController.group = self.selectedGroup;
    }
}

//MARK:- lifecycle

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleGroupCreated:) name:kGroupCreatedNotification object:nil];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //self.geofence = [[GTMeshGeofence alloc] init];
    //self.locationManager = [[LocationManager alloc] init];
    
    // Assign pairing handler
    [[GTPairingManager shared] setPairingHandler:self];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

//MARK:- Create frequency

- (GTFrequencyData *)createExampleFrequencySlot
{
    GTFrequencyData *frequencyData = [[GTFrequencyData alloc] init];
    [frequencyData setMaxPowerWatts:[FrequencySetPowerLevel doubleForData:PowerLevel_OneHalf]];
    [frequencyData setBandwidth:k11_80_kHZ];
    
    // There is a default set of frequencies that a slot can get populated with if you do not know what to use
    NSMutableArray<GTFrequencyChannelData*> *list = [NSMutableArray array];
    [list addObject:[[GTFrequencyChannelData alloc] initWithFrequency:150000000
                                                     isControlChannel:YES]];
    [list addObject:[[GTFrequencyChannelData alloc] initWithFrequency:151000000
                                                     isControlChannel:YES]];
    [list addObject:[[GTFrequencyChannelData alloc] initWithFrequency:151000000
                                                     isControlChannel:NO]];
    [list addObject:[[GTFrequencyChannelData alloc] initWithFrequency:151025000
                                                     isControlChannel:NO]];
    [frequencyData setChannelList:list];
    
    return frequencyData;
}

@end
