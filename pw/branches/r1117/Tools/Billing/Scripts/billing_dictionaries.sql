SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[EmployeeGroups] ([id], [name]) VALUES (1, N'Administrators')
INSERT [dbo].[EmployeeGroups] ([id], [name]) VALUES (2, N'Power users')
GO
SET IDENTITY_INSERT [dbo].[Employees] ON
INSERT [dbo].[Employees] ([id], [name], [password], [groupid]) VALUES (1, N'admin', HashBytes('MD5', 'password'), 1)
INSERT [dbo].[Employees] ([id], [name], [password], [groupid]) VALUES (2, N'power', HashBytes('MD5', 'password'), 2)
SET IDENTITY_INSERT [dbo].[Employees] OFF
GO

INSERT [dbo].[Settings] ([name], [value]) VALUES (N'PAYMENT.SYSTEM.CBT.ID',     CAST(N'2' AS nvarchar(1)))
INSERT [dbo].[Settings] ([name], [value]) VALUES (N'PAYMENT.SYSTEM.BONUSES.ID', CAST(N'1' AS nvarchar(1)))
INSERT [dbo].[Settings] ([name], [value]) VALUES (N'TRACE.ENABLED', CAST(N'2' AS nvarchar(1)))
INSERT [dbo].[Settings] ([name], [value]) VALUES (N'ADMIN.MAIL.ADDRESS', CAST(N'alimorov@tos.eu.org' AS nvarchar(19)))
INSERT [dbo].[Settings] ([name], [value]) VALUES (N'ADMIN.MAIL.PROFILE', CAST(N'#trace#' AS nvarchar(7)))
INSERT [dbo].[Settings] ([name], [value]) VALUES (N'FRAUD.CHECK.ENABLED', CAST(N'1' AS nvarchar(1)))
GO

INSERT [dbo].[PaymentSystems] ([id], [name], [priority], [description]) VALUES (1, N'BONUSES', 0, N'Bonuses')
INSERT [dbo].[PaymentSystems] ([id], [name], [priority], [description]) VALUES (2, N'CBT', -1, N'Closed beta testing virtual money')
INSERT [dbo].[PaymentSystems] ([id], [name], [priority], [description]) VALUES (3, N'LEGACY', 1, N'Legacy API money')
INSERT [dbo].[PaymentSystems] ([id], [name], [priority], [description]) VALUES (4, N'RM-1', 2, N'Test payment system')
GO

INSERT [dbo].[ProtocolSettings] ([id], [name], [loglevel], [timeout]) VALUES (101, N'Services', 2, 11)
INSERT [dbo].[ProtocolSettings] ([id], [name], [loglevel], [timeout]) VALUES (102, N'PaymentSystems', 2, 7)
INSERT [dbo].[ProtocolSettings] ([id], [name], [loglevel], [timeout]) VALUES (103, N'Reporting', 2, 8)
GO

INSERT [dbo].[OperationTypes] ([id], [name]) VALUES (101, N'Replenish by start money')
INSERT [dbo].[OperationTypes] ([id], [name]) VALUES (102, N'Replenish')
INSERT [dbo].[OperationTypes] ([id], [name]) VALUES (103, N'Promo code activation')
INSERT [dbo].[OperationTypes] ([id], [name]) VALUES (201, N'Expense')
INSERT [dbo].[OperationTypes] ([id], [name]) VALUES (202, N'Write-off by administrator')
INSERT [dbo].[OperationTypes] ([id], [name]) VALUES (301, N'Money transfer')
INSERT [dbo].[OperationTypes] ([id], [name]) VALUES (401, N'Promo code generation')
GO

INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1000, N'E_INVALID_ARG')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1001, N'E_CRC')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1002, N'E_EMAIL_EXISTS')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1003, N'E_USER_EXISTS')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1004, N'E_INVALID_USER')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1005, N'E_INVALID_PASSWORD')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1006, N'E_UNKNOWN_PAYMENT_SYSTEM')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1007, N'E_INVALID_ACCOUNT')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1008, N'E_OVERDRAFT')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1009, N'E_ALREADY_SUBSCRIBED')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1010, N'E_UNSUBSCRIBED')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1011, N'E_INVALID_SERVICE')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1012, N'E_ACCESS')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1013, N'E_INVALID_PROMO')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1014, N'E_INVALID_RESERVE')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-1015, N'E_OBSOLETE_RESERVE')
INSERT [dbo].[ErrorCodes] ([code], [name]) VALUES (-2000, N'E_UNEXPECTED')
GO

INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (101, N'Incoming service request')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (103, N'Incoming payment system request')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (102, N'Incoming legacy service request')

INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (201, N'Trace')

INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (501, N'User authorize')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (502, N'Create user')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (503, N'Write-off')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (504, N'Replenish')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (505, N'Transfer')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (506, N'Ban user')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (507, N'Un-ban user')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (508, N'Promo activation')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (509, N'Set user profile')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (510, N'Subscribe user')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (511, N'Unsubscribe user')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (512, N'Set service settings')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (513, N'Promo codes generation')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (514, N'Admin write-off')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (515, N'Set user password')
INSERT [dbo].[RecordTypes] ([id], [name]) VALUES (516, N'ReserveAmount')
GO

INSERT [dbo].[MailTemplates] ([id], [name], [subject], [body]) VALUES (101, N'FRAUD.LOGIN.YELLOW', N'Possible fraud detected while %USERNAME% authorization', N'Dear %USERDISPLAYNAME%. Possible fraud detected while authorization on %SERVICENAME%. Value of %PARAM1% is near the limit')
INSERT [dbo].[MailTemplates] ([id], [name], [subject], [body]) VALUES (102, N'FRAUD.LOGIN.RED', N'Fraud detected while %USERNAME% authorization', N'Dear %USERDISPLAYNAME%. Your account %USERNAME% banned due to exceeding of %PARAM1%')
INSERT [dbo].[MailTemplates] ([id], [name], [subject], [body]) VALUES (201, N'FRAUD.ADMIN.YELLOW', N'Possible fraud detected for user %USERNAME%', N'User  %USERNAME%. Dispaly name %USERDISPLAYNAME%. Possible fraud detected while authorization on %SERVICENAME%. Value of %PARAM1% is near the limit')
INSERT [dbo].[MailTemplates] ([id], [name], [subject], [body]) VALUES (202, N'FRAUD.ADMIN.RED', N'Fraud detected for user %USERNAME%', N'User  %USERNAME%. Dispaly name %USERDISPLAYNAME%. Possible fraud detected while authorization on %SERVICENAME%. Value of %PARAM1% exceeds the limit')
GO

INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'BONUSES.MAX.RATE', NULL, CAST(0.40 AS Decimal(15, 2)), N'maximal bonuses to real money rate')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'LOGIN.MAX.PER.HOUR', CAST(15.00 AS Decimal(15, 2)), CAST(20.00 AS Decimal(15, 2)), N'maximal count of login tries per hour')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'LOGIN.MAX.TRIES', CAST(3.00 AS Decimal(15, 2)), CAST(5.00 AS Decimal(15, 2)), N'maximal count of login tries')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'PAYMENT.MAX.AMOUNT', CAST(200.00 AS Decimal(15, 2)), CAST(300.00 AS Decimal(15, 2)), N'PAYMENT.MAX.AMOUNT')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'PAYMENT.MAX.AMOUNT.TRANSACTIONS.PER.DAY', NULL, CAST(1111.00 AS Decimal(15, 2)), N'PAYMENT.MAX.AMOUNT.TRANSACTIONS.PER.DAY')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'PAYMENT.MAX.AMOUNT.TRANSACTIONS.PER.WEEK', NULL, CAST(22222.00 AS Decimal(15, 2)), N'PAYMENT.MAX.AMOUNT.TRANSACTIONS.PER.WEEK')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'PAYMENT.MAX.COUNT.TRANSACTIONS.PER.DAY', NULL, CAST(2222.00 AS Decimal(15, 2)), N'PAYMENT.MAX.COUNT.TRANSACTIONS.PER.DAY')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'PAYMENT.MAX.COUNT.TRANSACTIONS.PER.WEEK', NULL, CAST(77777.00 AS Decimal(15, 2)), N'PAYMENT.MAX.COUNT.TRANSACTIONS.PER.WEEK')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'PROMO.MAX.PER.WEEK', NULL, CAST(60.00 AS Decimal(15, 2)), N'PROMO.MAX.PER.WEEK')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'PROMO.MAX.TRIES', CAST(2.00 AS Decimal(15, 2)), CAST(5.00 AS Decimal(15, 2)), N'PROMO.MAX.TRIES')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'TRANSFER.MAX.AMOUNT', CAST(100.00 AS Decimal(15, 2)), CAST(999999.00 AS Decimal(15, 2)), N'TRANSFER.MAX.AMOUNT')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'TRANSFER.MAX.AMOUNT.TRANSACTIONS.PER.DAY', NULL, CAST(200.00 AS Decimal(15, 2)), N'TRANSFER.MAX.AMOUNT.TRANSACTIONS.PER.DAY')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'TRANSFER.MAX.AMOUNT.TRANSACTIONS.PER.WEEK', NULL, CAST(200.00 AS Decimal(15, 2)), N'TRANSFER.MAX.AMOUNT.TRANSACTIONS.PER.WEEK')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'TRANSFER.MAX.COUNT.TRANSACTIONS.PER.DAY', NULL, CAST(200.00 AS Decimal(15, 2)), N'TRANSFER.MAX.COUNT.TRANSACTIONS.PER.DAY')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'TRANSFER.MAX.COUNT.TRANSACTIONS.PER.WEEK', NULL, CAST(2000.00 AS Decimal(15, 2)), N'TRANSFER.MAX.COUNT.TRANSACTIONS.PER.WEEK')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'WRITEOFF.MAX.AMOUNT', CAST(50.00 AS Decimal(15, 2)), CAST(999999.00 AS Decimal(15, 2)), N'WRITEOFF.MAX.AMOUNT')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'WRITEOFF.MAX.AMOUNT.TRANSACTIONS.PER.DAY', NULL, CAST(10000.00 AS Decimal(15, 2)), N'WRITEOFF.MAX.AMOUNT.TRANSACTIONS.PER.DAY')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'WRITEOFF.MAX.AMOUNT.TRANSACTIONS.PER.WEEK', NULL, CAST(100000.00 AS Decimal(15, 2)), N'WRITEOFF.MAX.AMOUNT.TRANSACTIONS.PER.WEEK')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'WRITEOFF.MAX.COUNT.TRANSACTIONS.PER.DAY', NULL, CAST(50.00 AS Decimal(15, 2)), N'WRITEOFF.MAX.COUNT.TRANSACTIONS.PER.DAY')
INSERT [dbo].[FraudSettings] ([code], [yellow], [red], [description]) VALUES (N'WRITEOFF.MAX.COUNT.TRANSACTIONS.PER.WEEK', NULL, CAST(500.00 AS Decimal(15, 2)), N'WRITEOFF.MAX.COUNT.TRANSACTIONS.PER.WEEK')
GO


INSERT dbo.Templates VALUES ('default', 'default', null, 0, '<template><amount>0</amount><service><id>11</id><settings /></service><service><id>19</id><settings /></service><service><id>24</id><settings /></service><service><id>14</id><settings /></service><service><id>8</id><settings /></service><service><id>7</id><settings /></service><service><id>5</id><settings /></service><service><id>3</id><settings /></service><service><id>1</id><settings /></service></template>', null)
GO

INSERT INTO dbo.Services VALUES  ('pw', 'pw', 0, HashBytes('MD5', 'service_password'), NULL, 0, 0)
GO
