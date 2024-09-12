/****** Object:  DdlTrigger [Version]    Script Date: 09/08/2013 16:06:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER [Version]
 ON DATABASE
 FOR DROP_TABLE, ALTER_TABLE, ALTER_PROCEDURE, DROP_PROCEDURE
 AS
 declare @verrrr int
 declare @scrrr1 xml

   PRINT 'Будем надеятся ниче не упадет...'

select @scrrr1 = EVENTDATA()
 select @verrrr = max(Vers) from [dbo].[BillingVersion]
 set @verrrr = @verrrr + 1

INSERT INTO [dbo].[BillingVersion]
            ([occurredat]
            ,[Vers]
            ,[Scr_param])
      VALUES(
            getdate()
            ,@verrrr
            ,@scrrr1  )
GO
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER OFF
GO
ENABLE TRIGGER [Version] ON DATABASE
GO
/****** Object:  User [billy]    Script Date: 09/08/2013 16:06:11 ******/
CREATE USER [bill] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  Schema [users]    Script Date: 09/08/2013 16:06:11 ******/
CREATE SCHEMA [users] AUTHORIZATION [dbo]
GO
/****** Object:  Table [dbo].[EmployeeGroups]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[EmployeeGroups](
	[id] [int] NOT NULL,
	[name] [varchar](20) NOT NULL,
 CONSTRAINT [XPKEmployeeGroups] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_api_zeroAwardMoney]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_zeroAwardMoney]
	@svcid	int,
	@users xml,
	@zeroAll bit,
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	declare @awardpsid int
	SELECT @awardpsid = dbo.sf_int_get_award_ps();	
	declare @amountWasZeroed decimal(15, 2)
	select @amountWasZeroed = 0

	if (@zeroAll = 1)
	BEGIN
		BEGIN TRANSACTION ZeroAwardMoney
		
		select @amountWasZeroed = sum(isnull(amount, 0)) from SubAccounts where systemid = @awardpsid;

		update SubAccounts 
		set amount = 0
		where systemid = @awardpsid

		COMMIT TRANSACTION ZeroAwardMoney

	END
	else
	BEGIN
		BEGIN TRANSACTION ZeroAwardMoney
		
		select @amountWasZeroed = sum(isnull(amount, 0)) from SubAccounts 
		where systemid = @awardpsid and
		accid in 
			(
				select accid from 
					(SELECT T.c.value('.', 'nvarchar(80)') AS name
					FROM @users.nodes('/user') T(c)) as t
					inner join Users u on t.[name] = u.[name]
				union
				select accountid from 
					(select id from 
						(SELECT T.c.value('.', 'nvarchar(80)') AS name
						FROM @users.nodes('/user') T(c)) as t
						inner join Users u on u.[name] = t.[name]) as c
					inner join UserServices us on c.id = us.userid
			);

		update SubAccounts 
		set amount = 0
		where systemid = @awardpsid and
		accid in 
			(
				select accid from 
					(SELECT T.c.value('.', 'nvarchar(80)') AS name
					FROM @users.nodes('/user') T(c)) as t
					inner join Users u on t.[name] = u.[name]
				union
				select accountid from 
					(select id from 
						(SELECT T.c.value('.', 'nvarchar(80)') AS name
						FROM @users.nodes('/user') T(c)) as t
						inner join Users u on u.[name] = t.[name]) as c
					inner join UserServices us on c.id = us.userid
			)

		COMMIT TRANSACTION ZeroAwardMoney
	END
	
	-- log request ================================================================================
	--typeId = 517 - zeroAwardMoney
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		'amountWasZeroed=' + isnull(cast(@amountWasZeroed as varchar(10)), '') + 
		':zeroAll=' + isnull(cast(@zeroAll as varchar(1)), '') +
		':users=' + isnull(cast(@users as varchar(7999)), '')
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 517, @serviceid=@svcid, @userid = null, @operationid = null, 
		@amount = null, @parameters = @content, @result = @error, @error = @errlog OUTPUT
	-- end log request ============================================================================
	
	IF @ERROR <> 0
		RETURN -1;
	
	select @amountWasZeroed as zeroedAmount
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_awardCounterAchiev]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_awardCounterAchiev]
	@achievId int,
	@userid int,
	@old int,
	@incoming int,
	@meta xml,
	@returnValue nvarchar(max) output
AS
BEGIN
	declare @fulfiled bit
	declare @maxFromMeta int
	declare @new int
	
	select @fulfiled = 0
	select @maxFromMeta = @meta.value('(./meta/@max)[1]', 'int') 		
	select @new = @old + @incoming

	if (@old < @maxFromMeta and @new >= @maxFromMeta)
		select @fulfiled = 1
	if ( @old is null )
	BEGIN
		select @new = @incoming
		INSERT UserHasAchievement (userId, achievId, fulfiled, specData)
			VALUES (@userId, @achievID, @fulfiled, convert (xml, cast(@new as nvarchar)))
	END
	else 
	BEGIN
		UPDATE UserHasAchievement
			SET fulfiled = @fulfiled, specData = convert (xml, cast(@new as nvarchar))
				WHERE userId = @userId and achievId = @achievID
	END

	select @returnValue = cast(@new as nvarchar(max))
END
GO
/****** Object:  Table [dbo].[ErrorCodes]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ErrorCodes](
	[code] [int] NOT NULL,
	[name] [varchar](80) NOT NULL,
 CONSTRAINT [PK_ErrorCodes] PRIMARY KEY CLUSTERED 
(
	[code] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[FraudSettings]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[FraudSettings](
	[code] [varchar](50) NOT NULL,
	[yellow] [decimal](15, 2) NULL,
	[red] [decimal](15, 2) NOT NULL,
	[description] [varchar](200) NOT NULL,
 CONSTRAINT [PK_FraudSettings] PRIMARY KEY CLUSTERED 
(
	[code] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Gameleads]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Gameleads](
	[string] [nvarchar](max) NULL,
	[id] [int] IDENTITY(1,1) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getAccountCBTDetails]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 31/03/2010
-- Description:	Gets AccountCBT details
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_getAccountCBTDetails] 
	@userID INT
AS
BEGIN
	SET NOCOUNT ON;

	SELECT AC.name, SA.amount, SV.id, SV.name FROM dbo.SubAccounts AS SA, dbo.Accounts  AS AC 
	LEFT JOIN UserServices  AS US ON AC.id = US.accountid
	LEFT JOIN Services AS SV ON US.serviceid = SV.id
	WHERE SA.accid = AC.id  AND SA.systemid = dbo.sf_int_get_cbt_ps()
	AND AC.userid = @userID
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_GetAccountNameByUserIDAndServiceID]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 05/04/2010
-- Description:	Helper procedure
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_GetAccountNameByUserIDAndServiceID] 
	-- Add the parameters for the stored procedure here
	@UserID INT,
	@ServiceID INT
AS
BEGIN
	SET NOCOUNT ON;

	SELECT AC.NAME FROM dbo.UserServices US
	INNER JOIN Accounts AC ON AC.id=US.accountid
	WHERE US.serviceid=@ServiceID AND US.userid=@userID 
END
GO
/****** Object:  Table [dbo].[Legacy]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Legacy](
	[newId] [int] NULL,
	[oldIp] [varchar](20) NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getBonusesHistory]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/11
-- Description:	Retrieves bonuses payments history/

CREATE PROCEDURE [dbo].[sp_gui_getBonusesHistory]
	-- user name
	@userID INT,
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- from amount
	@fromAmount DECIMAL,
	-- to amount
	@toAmount DECIMAL,
	-- payment system
	@reason TEXT,
	-- error code
	@error int OUTPUT
AS
BEGIN

	SELECT @ERROR = 0;
	DECLARE @count INT;
	
	-- check parameters
    IF @UserID IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END	
	
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @count=COUNT(*) FROM Users WHERE id=@userID
		IF @count=0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END
	
	IF @ERROR <> 0
		RETURN -1;
	
	SELECT OP.AMOUNT, OP.EXECUTEDAT, OP.reason AS REASON FROM DBO.OPERATIONS AS OP
				WHERE  type>=100 AND type<200 AND OP.userid = @userID AND OP.systemid=1
					AND executedat BETWEEN @fromDate AND @toDate 
					AND OP.amount BETWEEN @fromAmount AND @toAmount
					AND OP.reason LIKE @reason
				ORDER BY OP.executedat ASC
	RETURN 0;
END
GO
/****** Object:  Table [dbo].[MailTemplates]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[MailTemplates](
	[id] [int] NOT NULL,
	[name] [varchar](50) NOT NULL,
	[subject] [nvarchar](255) NOT NULL,
	[body] [nvarchar](max) NOT NULL,
 CONSTRAINT [PK_MailTemplates] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getPaymentsByPartner]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_gui_getPaymentsByPartner]
	@dateFrom datetime,
	@dateTo datetime,
	@partnerId nvarchar(10),
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	--declare @dateFrom datetime, @dateTo datetime, @partnerId int
	--select @dateFrom = '20100824 13:16:45'
	--select @dateTo = '20100825 13:16:45'
	--select @partnerId = 1

	select sum(o.amount) as amount, o.userid from Users u
	inner join Operations o on u.id = o.userid
	where u.partnerid = @partnerId and [type] = 102
	and o.executedat >= @dateFrom and o.executedat < @dateTo
	group by o.userid
	--order by amount desc
	
	RETURN 0;
END
GO
/****** Object:  Table [dbo].[nival_billing_logs]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[nival_billing_logs](
	[id] [int] NULL,
	[money] [real] NULL,
	[create_date] [datetime] NULL,
	[pay_date] [datetime] NULL,
	[transfer_date] [datetime] NULL,
	[status] [smallint] NULL,
	[user_id] [int] NULL,
	[game_id] [int] NULL,
	[secret] [nvarchar](32) NULL,
	[merchant_id] [int] NULL,
	[zzmoney] [real] NULL,
	[cas_id] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  UserDefinedFunction [dbo].[RegexMatch]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[RegexMatch]
    (
      @pattern VARCHAR(2000),
      @matchstring VARCHAR(MAX)--Varchar(8000) got SQL Server 2000
    )
RETURNS INT
/* The RegexMatch returns True or False, indicating if the regular expression matches (part of) the string. (It returns null if there is an error).
When using this for validating user input, you'll normally want to check if the entire string matches the regular expression. To do so, put a caret at the start of the regex, and a dollar at the end, to anchor the regex at the start and end of the subject string.
*/
AS BEGIN
    DECLARE @objRegexExp INT,
        @objErrorObject INT,
        @strErrorMessage VARCHAR(255),
        @hr INT,
        @match BIT

    SELECT  @strErrorMessage = 'creating a regex object'
    EXEC @hr= sp_OACreate 'VBScript.RegExp', @objRegexExp OUT
    IF @hr = 0
        EXEC @hr= sp_OASetProperty @objRegexExp, 'Pattern', @pattern
        --Specifying a case-insensitive match
    IF @hr = 0
        EXEC @hr= sp_OASetProperty @objRegexExp, 'IgnoreCase', 1
        --Doing a Test'
    IF @hr = 0
        EXEC @hr= sp_OAMethod @objRegexExp, 'Test', @match OUT, @matchstring
    IF @hr <> 0
        BEGIN
            RETURN NULL
        END
    EXEC sp_OADestroy @objRegexExp
    RETURN @match
   END
GO
/****** Object:  Table [dbo].[OperationTypes]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[OperationTypes](
	[id] [int] NOT NULL,
	[name] [varchar](80) NOT NULL,
 CONSTRAINT [XPKOperationTypes] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  UserDefinedFunction [dbo].[sf_decimal_get_comission]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/25
-- Description:	Gets comission

CREATE FUNCTION [dbo].[sf_decimal_get_comission]()
RETURNS INT
AS
BEGIN
RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getTransfersHistory]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_gui_getTransfersHistory]
	-- user name
	@userID INT,
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- from amount
	@fromAmount DECIMAL,
	-- to amount
	@toAmount DECIMAL,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;

	if not exists (select 1 FROM Users WHERE id = @userID )
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		RETURN -1;
	END
	
	IF (@fromDate IS NULL)
		SELECT @fromDate = CONVERT(DATETIME, '1900/01/01 00:00')
		
	IF (@toDate IS NULL)
		SELECT @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	
	SELECT AMOUNT, EXECUTEDAT, REASON, SRCACCID, DESTACCID 
			from dbo.Operations
				where [type] = 301 and userid = @userid
				and executedat between @fromDate and @toDate
				and amount between @fromAmount and @toAmount
				ORDER BY executedat DESC
	
	RETURN 0;
END
GO
/****** Object:  Table [dbo].[PartnerPrograms]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PartnerPrograms](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](80) NOT NULL,
	[authorizationClass] [varchar](80) NULL,
 CONSTRAINT [XPKPartnerPrograms] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_check_hash]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	does checking of value by its hash

CREATE FUNCTION [dbo].[sf_int_check_hash](@value varchar(4000),@hash varchar(4000)) 
RETURNS bit
AS
BEGIN
	if (@value is NULL or @hash is NULL )
		RETURN 0
	
	if (@hash = HashBytes('MD5', @value))
		RETURN 1

	RETURN 0
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_dec_to_base]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[sf_int_dec_to_base] (@VAL AS BIGINT ,@BASE AS INT)
RETURNS VARCHAR(63)AS
BEGIN
	IF (@VAL<0) OR (@BASE < 2) OR (@BASE> 36) 
		RETURN NULL;   
	/* VARIABLE TO HOLD FINAL ANSWER */  
	DECLARE @ANSWER AS VARCHAR(63);   
	/* FOLLOWING VARIABLE CONTAINS ALL      
	POSSIBLE ALPHA NUMERIC LETTERS FOR ANY VALID BASE  */  
	DECLARE @ALLDIGITS AS VARCHAR(36);  
	SET @ALLDIGITS='0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'   
	/* SET THE INITIAL VALUE OF      FINAL ANSWER AS EMPTY STRING   */  
	SET @ANSWER='';   
	/* LOOP WHILE THE SOURCE VALUE REMAINS GREATER THAN 0 */  
	WHILE @VAL>0  
	BEGIN    
		SET @ANSWER=SUBSTRING(@ALLDIGITS,(@VAL % @BASE)  + 1,1) + @ANSWER;    
		SET @VAL = @VAL / @BASE;  
	END   /* RETURN THE FINAL ANSWER */  
RETURN @ANSWER;END
GO
/****** Object:  Table [dbo].[PartnerUserHash]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PartnerUserHash](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[userId] [int] NOT NULL,
	[partnerId] [int] NOT NULL,
	[partnerHash] [nvarchar](32) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_generate_hash]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	Generates hash of passwords, strings and so on
-- =============================================
CREATE FUNCTION [dbo].[sf_int_generate_hash] (	@val varchar(4000))

RETURNS varchar(4000)
AS
BEGIN
	DECLARE @ResultVar varchar(4000);
	SELECT @ResultVar = HashBytes('MD5', @val); 
	RETURN @ResultVar

END
GO
/****** Object:  Table [dbo].[PaymentSystems]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PaymentSystems](
	[id] [int] NOT NULL,
	[name] [nvarchar](80) NOT NULL,
	[priority] [int] NOT NULL,
	[description] [nvarchar](200) NULL,
	[ownSvcId] [int] NULL,
 CONSTRAINT [XPKPaymentSystems] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_get_award_ps]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[sf_int_get_award_ps]() 
RETURNS INT
AS
BEGIN
	RETURN 19
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_get_bonuses_ps]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/05
-- Description:	Retrieves id of bonus payment system

CREATE FUNCTION [dbo].[sf_int_get_bonuses_ps]() 
RETURNS INT
AS
BEGIN
	RETURN 1
END
GO
/****** Object:  Table [dbo].[PaymentSystemsMigr]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PaymentSystemsMigr](
	[id] [int] NOT NULL,
	[name] [nvarchar](80) NOT NULL,
 CONSTRAINT [XPKPaymentSystemsM] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_get_cbt_ps]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/05
-- Description:	Retrieves id of bonus payment system

CREATE FUNCTION [dbo].[sf_int_get_cbt_ps]() 
RETURNS INT
AS
BEGIN
	RETURN 2
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_get_legacy_ps]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/05
-- Description:	Retrieves id of bonus payment system

CREATE FUNCTION [dbo].[sf_int_get_legacy_ps]() 
RETURNS INT
AS
BEGIN
	RETURN 4
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_regexp_match]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[sf_int_regexp_match]
    (
        @source varchar(8000),
        @regexp varchar(1000),
        @ignorecase bit = 0
    )
RETURNS bit
AS
    BEGIN
        DECLARE @hr integer
        DECLARE @objRegExp integer
        DECLARE @objMatches integer
        DECLARE @objMatch integer
        DECLARE @count integer
        DECLARE @results bit
        
        EXEC @hr = sp_OACreate 'VBScript.RegExp', @objRegExp OUTPUT
        IF @hr <> 0 BEGIN
            SET @results = 0
            RETURN @results
        END
        EXEC @hr = sp_OASetProperty @objRegExp, 'Pattern', @regexp
        IF @hr <> 0 BEGIN
            SET @results = 0
            RETURN @results
        END
        EXEC @hr = sp_OASetProperty @objRegExp, 'Global', false
        IF @hr <> 0 BEGIN
            SET @results = 0
            RETURN @results
        END
        EXEC @hr = sp_OASetProperty @objRegExp, 'IgnoreCase', @ignorecase
        IF @hr <> 0 BEGIN
            SET @results = 0
            RETURN @results
        END    
        EXEC @hr = sp_OAMethod @objRegExp, 'Test', @results OUTPUT, @source
        IF @hr <> 0 BEGIN
            SET @results = 0
            RETURN @results
        END
        EXEC @hr = sp_OADestroy @objRegExp
        IF @hr <> 0 BEGIN
            SET @results = 0
            RETURN @results
        END
    RETURN @results
    END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_checkFraudPayment]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does fraud checking of payments operations
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_checkFraudPayment]
	-- amount of operation
	@amount DECIMAL(15,2),
	-- id of service
	@svcid INT,
	-- id of users
	@userid INT,
	-- error code
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @switch=0
    	RETURN 0;
	
	DECLARE @value DECIMAL(15,2);
	DECLARE @paramName VARCHAR(80);
	DECLARE @detectedName VARCHAR(80);
	
	DECLARE	@ret INT;
	SELECT @ret = 0;
	DECLARE	@ret_op INT;
	
	-- check input parameters
	IF @svcid IS NULL OR @userid IS NULL OR @amount IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END;
	
	-- check for max operation amount ==============================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'PAYMENT.MAX.AMOUNT'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amount, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	-- check count and amount per day ==================================
	DECLARE @amtpd DECIMAL(15,2);
	DECLARE @cntpd DECIMAL(15,2);

	IF @error = 0 AND @ret<>2
	BEGIN
		SELECT @amtpd = SUM(amount), @cntpd = COUNT(*)
			FROM dbo.Operations WHERE userid=@userid AND type=102 AND executedat>= DATEADD(day,-1,GETDATE());
		set @amtpd = case when @amtpd IS NULL THEN 0 ELSE @amtpd END + @amount;
		set @cntpd = @cntpd+1;
		EXEC dbo.sp_int_trace 'Amount and count of payments of user per day', @amtpd, @cntpd
	END

	---- check amount per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'PAYMENT.MAX.AMOUNT.TRANSACTIONS.PER.DAY';
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amtpd, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	---- check count per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'PAYMENT.MAX.COUNT.TRANSACTIONS.PER.DAY'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @cntpd, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- check count and amount per weak =================================
	DECLARE @amtpw DECIMAL(15,2);
	DECLARE @cntpw DECIMAL(15,2);

	IF @error = 0 AND @ret<>2
	BEGIN
		SELECT @amtpw = SUM(amount), @cntpw = COUNT(*) 
			FROM dbo.Operations WHERE userid=@userid AND type=102 AND executedat>= DATEADD(day,-7,GETDATE());
		set @amtpw = case when @amtpw IS NULL THEN 0 ELSE @amtpw END + @amount;
		set @cntpw = @cntpw+1;
		EXEC dbo.sp_int_trace 'Amount and count of payments of user per weak', @amtpw, @cntpw
	END

	---- check amount per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'PAYMENT.MAX.AMOUNT.TRANSACTIONS.PER.WEEK';
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amtpw, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	---- check count per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'PAYMENT.MAX.COUNT.TRANSACTIONS.PER.WEEK'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @cntpw, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- check for amount of bonuses ======================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'BONUSES.MAX.RATE';
		DECLARE @rate DECIMAL(15,2);
		SET @rate = dbo.sf_int_getBonusesRate();

		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @rate, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- send mail to admin, if non zero level detected =======================================
	IF @error=0 AND @ret >0
		EXEC [dbo].[sp_int_send_admin_fraud_mail]	 @svcid = @svcid,
													 @userid = @userid,
													 @parameter = @detectedName,
													 @level = @ret,
													 @error = @error OUTPUT	
		
	IF @error = 0 AND @ret = 2
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
	
	IF @error=0
		RETURN 0;
		
	RETURN -1;	
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_resolve_account_owner]    Script Date: 09/08/2013 16:06:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/03
-- Description:	Retrieves id of owner of the account

-- =============================================
CREATE FUNCTION [dbo].[sf_int_resolve_account_owner] (@accid int)
RETURNS int
AS
BEGIN
	DECLARE @RESULTVAR INT;
	SELECT @RESULTVAR = RC.ID FROM (
	SELECT US.ID FROM USERS as US WHERE US.ACCID = @accid
	UNION 
	SELECT US.ID FROM USERS as US, dbo.UserServices AS USC
		 WHERE USC.userid = US.ID AND USC.accountid = @accid ) AS RC
	
	RETURN @RESULTVAR
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_checkFraudTransfer]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does fraud checking of transfer operations
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_checkFraudTransfer]
	-- amount of operation
	@amount DECIMAL(15,2),
	-- id of service
	@svcid INT,
	-- id of users
	@userid INT,
	-- error code
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @switch=0
    	RETURN 0;
	
	DECLARE @value DECIMAL(15,2);
	DECLARE @paramName VARCHAR(80);
	DECLARE @detectedName VARCHAR(80);
	
	DECLARE	@ret INT;
	SELECT @ret = 0;
	DECLARE	@ret_op INT;
	
	-- check input parameters
	IF @svcid IS NULL OR @userid IS NULL OR @amount IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END;
	
	-- check for max operation amount ==============================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'TRANSFER.MAX.AMOUNT'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amount, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	-- check count and amount per day ==================================
	DECLARE @amtpd DECIMAL(15,2);
	DECLARE @cntpd DECIMAL(15,2);

	IF @error = 0 AND @ret<>2
	BEGIN
		SELECT @amtpd = SUM(amount), @cntpd = COUNT(*)
			FROM dbo.Operations WHERE userid=@userid AND type=102 AND executedat>= DATEADD(day,-1,GETDATE());
		set @amtpd = case when @amtpd IS NULL THEN 0 ELSE @amtpd END + @amount;
		set @cntpd = @cntpd+1;
		EXEC dbo.sp_int_trace 'Amount and count of payments of user per day', @amtpd, @cntpd
	END

	---- check amount per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'TRANSFER.MAX.AMOUNT.TRANSACTIONS.PER.DAY';
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amtpd, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	---- check count per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'TRANSFER.MAX.COUNT.TRANSACTIONS.PER.DAY'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @cntpd, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- check count and amount per weak =================================
	DECLARE @amtpw DECIMAL(15,2);
	DECLARE @cntpw DECIMAL(15,2);

	IF @error = 0 AND @ret<>2
	BEGIN
		SELECT @amtpw = SUM(amount), @cntpw = COUNT(*) 
			FROM dbo.Operations WHERE userid=@userid AND type=102 AND executedat>= DATEADD(day,-7,GETDATE());
		set @amtpw = case when @amtpw IS NULL THEN 0 ELSE @amtpw END + @amount;
		set @cntpw = @cntpw+1;
		EXEC dbo.sp_int_trace 'Amount and count of payments of user per weak', @amtpw, @cntpw
	END

	---- check amount per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'TRANSFER.MAX.AMOUNT.TRANSACTIONS.PER.WEEK';
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amtpw, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	---- check count per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'TRANSFER.MAX.COUNT.TRANSACTIONS.PER.WEEK'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @cntpw, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- check for amount of bonuses ======================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'BONUSES.MAX.RATE';
		DECLARE @rate DECIMAL(15,2);
		SET @rate = dbo.sf_int_getBonusesRate();

		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @rate, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- send mail to admin, if non zero level detected =======================================
	IF @error=0 AND @ret >0
		EXEC [dbo].[sp_int_send_admin_fraud_mail]	 @svcid = @svcid,
													 @userid = @userid,
													 @parameter = @detectedName,
													 @level = @ret,
													 @error = @error OUTPUT	
		
	IF @error = 0 AND @ret = 2
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
	
	IF @error=0
		RETURN 0;
		
	RETURN -1;	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_banUser]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Bans user on service

CREATE PROCEDURE [dbo].[sp_int_banUser]
	-- id of service
	@serviceid INT,
	-- id of user
	@userid INT,
	-- reason of operation, cannot be null
	@reason TEXT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	-- check parameters	
	IF @USERID IS NULL OR @serviceid IS NULL OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 

    IF @ERROR = 0
	BEGIN    
		BEGIN TRANSACTION T_BAN_USER;
   
		DECLARE @USID INT;  
		-- check subscribtion   
		DECLARE @USACTIVE BIT;
		SELECT @USID = ID, @USACTIVE = ACTIVE FROM USERSERVICES 
			WHERE USERID=@userid AND serviceid = @SERVICEID;

		IF @USACTIVE IS NULL OR @USACTIVE <> 1
		BEGIN
			EXEC dbo.sp_int_trace 'Service un-subscriped', @userid, @SERVICEID;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		END;

		IF @ERROR=0
		BEGIN
			EXEC dbo.sp_int_trace 'Ban user on service', @userid, @SERVICEID, @USID;
			UPDATE USERSERVICES SET ban = 1, banReason = @reason WHERE ID = @USID
			IF @@ROWCOUNT = 0
			BEGIN
				EXEC dbo.sp_int_trace 'Cannot update user service record', @USID, @@ERROR;
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END
		
		END	

		if @ERROR<>0
			ROLLBACK TRANSACTION T_BAN_USER;
		ELSE
			COMMIT TRANSACTION T_BAN_USER;
	END

	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_generate_rnd_string]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE  [dbo].[sp_int_generate_rnd_string] 
	@digits AS INT,
	@devider AS CHAR(1) = '-',
	@groups AS INT = 4,
	@random AS VARCHAR(100) OUTPUT
AS
BEGIN
	DECLARE @counter INT, @ValidCharactersLength INT
	DECLARE @RandomNumber float
	DECLARE @RandomNumberInt tinyint
	DECLARE @ValidCharacters varchar(255)

	SET @ValidCharacters = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
	SET @ValidCharactersLength = len(@ValidCharacters)
	SET @RandomNumber = 0
	SET @RandomNumberInt = 0
	SET @random = '';

	SET @RandomNumber = RAND(CHECKSUM(NEWID()));

	SET @counter = 1
	WHILE @counter <= @digits
	BEGIN
			IF (NOT @devider IS NULL AND @counter<>1) AND (@counter-1)%@groups = 0
				SET @random = @random + @devider; 
					
			SET @RandomNumberInt = Convert(tinyint, ((@ValidCharactersLength - 1) * @RandomNumber + 1));

			SET @counter = @counter + 1;
			SET @random = @random + SUBSTRING(@ValidCharacters, @RandomNumberInt, 1);
			SET @RandomNumber = Rand();
	END

END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_linear_approximation]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/05/7

CREATE PROCEDURE [dbo].[sp_int_linear_approximation]
AS
BEGIN

	DECLARE @MX FLOAT;
	DECLARE @MY FLOAT;
	DECLARE @P FLOAT;
	DECLARE @SQ FLOAT;
	DECLARE @CNT FLOAT;
	DECLARE @A FLOAT;
	DECLARE @B FLOAT;

	SELECT @MX=SUM(X), @MY=SUM(y), @CNT = COUNT(*) FROM #TMP_DATA;

	IF (@CNT < 2)
		RETURN -1;

	SET @MX = @MX/@CNT
	SET @MY = @MY/@CNT

	SELECT @P = SUM((X-@MX)*(y-@MY)), @SQ =SUM(SQUARE(X-@MX)) FROM #TMP_DATA;

	SET @B = @P / @SQ
	SET @A = @MY- @B*@MX
	
	EXEC dbo.sp_int_trace 'y = bx+a, b=,a=  B*1+A=', @B, @A 

	SELECT X, Y, (@B*X +@A) AS YL  FROM #TMP_DATA;

END
GO
/****** Object:  Table [dbo].[ProtocolSettings]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ProtocolSettings](
	[id] [int] NOT NULL,
	[name] [varchar](80) NOT NULL,
	[loglevel] [int] NOT NULL,
	[timeout] [int] NULL,
 CONSTRAINT [XPKProtocolSettings] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_int_create_account]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	Creates new account
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_create_account]
	--id of owner
	@userid INT
AS
BEGIN
	DECLARE @myid uniqueidentifier
	SET @myid = NEWID()
	INSERT INTO dbo.Accounts (name,userid) values ( 'AC-' + CONVERT(varchar(50),@myid), @userid);
	DECLARE @ResultVar int;
	return SCOPE_IDENTITY();
END
GO
/****** Object:  Table [dbo].[RecordTypes]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[RecordTypes](
	[id] [int] NOT NULL,
	[name] [varchar](80) NOT NULL,
 CONSTRAINT [XPKRecordTypes] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ReplenishTemp]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ReplenishTemp](
	[userid] [int] NULL,
	[zzmoney] [real] NULL,
	[transfer_date] [datetime] NULL,
	[merchant_id] [int] NULL,
	[username] [nvarchar](32) NULL,
	[paym_name] [nvarchar](80) NULL,
	[newPaymId] [int] NULL,
	[newuserid] [int] NULL,
	[accid] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[sp_int_replenish]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_replenish]
	@USERID INT,
	@ACCID INT,
	@PAYMENTSYSTEM INT,
	@AMOUNT DECIMAL(15,2),
	@AWARD DECIMAL(15,2),
	@TYPE INT,
	@REASON text,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @SUBACCID INT;

	IF  @USERID IS NULL OR @ACCID IS NULL OR @PAYMENTSYSTEM IS NULL OR @AMOUNT IS NULL OR @AMOUNT<=0
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END 
	
	BEGIN TRANSACTION T_REPLENISH

	-- INSERT OPERATION ===========================
	IF @ERROR = 0
	BEGIN
		
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, DESTACCID, SYSTEMID, REASON)
			VALUES (@AMOUNT, @USERID, GETDATE(), @TYPE, @ACCID, @PAYMENTSYSTEM, @REASON)
		IF @@ERROR <> 0
        BEGIN
        	EXEC dbo.sp_int_trace 'Unable to create new operation', @@ERROR
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END            
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END
    
    IF @ERROR = 0
	BEGIN
    	EXEC [dbo].[sp_int_replenish_acc]  @OPERID, @ACCID, @PAYMENTSYSTEM, @AMOUNT, @error OUTPUT ;
	END
	
	--operation for award
	IF (@ERROR = 0 and @AWARD > 0)
	BEGIN
		declare @awardpsid int
			SELECT @awardpsid = dbo.sf_int_get_award_ps();		

		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, DESTACCID, SYSTEMID, REASON)
			VALUES (@AWARD, @USERID, GETDATE(), @TYPE, @ACCID, @awardpsid, ('awardToOpID:' + cast(@operid as nvarchar(10))))
		IF @@ERROR <> 0
        BEGIN
        	EXEC dbo.sp_int_trace 'Unable to create new operation', @@ERROR
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END

		IF @ERROR = 0
		BEGIN
    		EXEC [dbo].[sp_int_replenish_acc]  @OPERID, @ACCID, @awardpsid, @AWARD, @error OUTPUT ;
		END
	END
	
	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_REPLENISH
		RETURN 0;
	END
	ROLLBACK TRANSACTION T_REPLENISH
	RETURN -1
END
GO
/****** Object:  Table [dbo].[ReplenishTempKW]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ReplenishTempKW](
	[userid] [int] NULL,
	[amount] [decimal](15, 2) NULL,
	[pubdate] [datetime] NULL,
	[remoteaddr] [nvarchar](8) NULL,
	[kwAccountId] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[sp_int_replenish_acc]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/04
-- Description:	Replenishes the account
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_replenish_acc]
	@OPERID INT,
	@ACCID INT,
	@PAYMENTSYSTEM INT,
	@AMOUNT DECIMAL(15,2),
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @SUBACCID INT;
  
    -- create/update sub-account 
	SELECT @SUBACCID = ID FROM DBO.SUBACCOUNTS WHERE ACCID = @ACCID AND SYSTEMID = @PAYMENTSYSTEM
	if NOT @SUBACCID IS NULL
		BEGIN
		-- CHANGE BALANCE =============================	
			UPDATE DBO.SUBACCOUNTS
				SET AMOUNT = AMOUNT + @AMOUNT 
				WHERE ID = @SUBACCID 
			IF @@ROWCOUNT = 0
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END
	ELSE
		BEGIN
		-- CREATE BALANCE =============================	
			INSERT INTO DBO.SUBACCOUNTS (SYSTEMID, AMOUNT, ACCID)
				VALUES (@PAYMENTSYSTEM, @AMOUNT, @accid);
			IF @@ERROR <> 0
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			ELSE
				SELECT @SUBACCID = SCOPE_IDENTITY();
		END


    IF @ERROR = 0
    BEGIN
		-- INSERT TRANSACTION =========================
        INSERT INTO dbo.Transactions (operationid, subaccid, amount)
			VALUES (@OPERID, @SUBACCID, @AMOUNT)
		IF @@ERROR <> 0
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');        
    END
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_send_raw_mail]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- does sending of message
CREATE PROCEDURE [dbo].[sp_int_send_raw_mail] 
	-- dest user name
	@to varchar(100) = NULL,
	-- subject of message
	@subject varchar(100),
	-- body of messsage
	@body varchar(4000),
	-- error code, if any
	@error INT OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @error = 0;
	DECLARE @profile VARCHAR(80);

	IF @error = 0 AND @to IS NULL
	BEGIN
		SET @to =  CONVERT(VARCHAR(80),dbo.sf_get_config_value('ADMIN.MAIL.ADDRESS'));
		IF @to IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
	END
	
	IF @error = 0
	BEGIN
		SET @profile =  CONVERT(VARCHAR(80),dbo.sf_get_config_value('ADMIN.MAIL.PROFILE'));
		IF @profile IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
	END

	IF @error = 0  AND @profile = '#trace#'
		EXEC dbo.sp_int_trace 'Send mail to trace', @To, @Subject, @Body
	ELSE		
		BEGIN	
			EXEC msdb..sp_send_dbmail	@profile_name = @profile,
										@recipients = @To,
										@subject = @Subject,
										@body = @Body;
										
			IF @@ERROR<>0
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
		END

	IF @error = 0
		RETURN 0;

	RETURN -1;											
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_split]    Script Date: 09/08/2013 16:06:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/04/27
-- Description:	Does split of string

CREATE FUNCTION [dbo].[sf_int_split] (@s VARCHAR(8000),@sep char(1)) 
RETURNS table
AS
RETURN 
(
	WITH Pieces(pn, start, stop) AS 
	(
		SELECT 1, 1, CHARINDEX(@sep, @s)
		UNION ALL
		SELECT pn + 1, stop + 1, CHARINDEX(@sep, @s, stop + 1)
			FROM Pieces
			WHERE stop > 0
    )
    SELECT pn AS pos,
		SUBSTRING(@s, start, CASE WHEN stop > 0 THEN stop-start ELSE 8000 END) AS part
    FROM Pieces
)
GO
/****** Object:  Table [dbo].[Settings]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Settings](
	[name] [varchar](40) NOT NULL,
	[value] [sql_variant] NOT NULL,
 CONSTRAINT [XPKSettings] PRIMARY KEY NONCLUSTERED 
(
	[name] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_int_split]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/05/24
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_split]
	@s VARCHAR(8000),
	@sep CHAR(1)

AS
BEGIN
	DECLARE @t TABLE(pos INT, part varchar(80));
	DECLARE @end INT, @start INT, @pos INT;
	SET @start = 1;
	SET @end = 1;
	SET @pos = 1;
	
	SET NOCOUNT ON;
	
	WHILE @end >0
	BEGIN
		SET @end = CHARINDEX(@sep, @s, @start);
		INSERT INTO @t
		VALUES (@pos, SUBSTRING(@s, @start, CASE WHEN @end > 0 THEN @end-@start ELSE 8000 END) )
		SET @start = @end + 1
		SET @pos = @pos + 1
	END
		
	SET NOCOUNT OFF;	
	SELECT * FROM @t;	
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_trace]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/04
-- Description:	Traces parameters
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_trace]
	@MARK VARCHAR(100),
	@P1 sql_variant = '~##~',
	@P2 sql_variant = '~##~',    
    @P3 sql_variant = '~##~',
    @P4 sql_variant = '~##~',    
    @P5 sql_variant = '~##~',
    @P6 sql_variant = '~##~'
AS
BEGIN
	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('TRACE.ENABLED'));
   	if @switch=0
    	RETURN 0;
         
	DECLARE @fullmsg VARCHAR(MAX);
	
	SET @fullmsg = CONVERT(VARCHAR(40),GETDATE(),20) + ' : ' + @MARK;
	
	IF @P1 IS NULL 
		SET @fullmsg = @fullmsg + ':[null]';	
	ELSE IF @P1 <> '~##~'
		SET @fullmsg = @fullmsg + ':[' + CONVERT(VARCHAR(400), @P1) + ']';
		 
	IF @P2 IS NULL 
		SET @fullmsg = @fullmsg + ':[null]';	
	ELSE IF @P2 <> '~##~'
		SET @fullmsg = @fullmsg + ':[' + CONVERT(VARCHAR(400), @P2) + ']';
		 
	IF @P3 IS NULL 
		SET @fullmsg = @fullmsg + ':[null]';	
	ELSE IF @P3 <> '~##~'
		SET @fullmsg = @fullmsg + ':[' + CONVERT(VARCHAR(400), @P3) + ']';
		 
	IF @P4 IS NULL 
		SET @fullmsg = @fullmsg + ':[null]';	
	ELSE IF @P4 <> '~##~'
		SET @fullmsg = @fullmsg + ':[' + CONVERT(VARCHAR(400), @P4) + ']';
		 
	IF @P5 IS NULL 
		SET @fullmsg = @fullmsg + ':[null]';	
	ELSE IF @P5 <> '~##~'
		SET @fullmsg = @fullmsg + ':[' + CONVERT(VARCHAR(400), @P5) + ']';
	
	IF @P6 IS NULL 
		SET @fullmsg = @fullmsg + ':[null]';	
	ELSE IF @P6 <> '~##~'
		SET @fullmsg = @fullmsg + ':[' + CONVERT(VARCHAR(400), @P6) + ']';
	
		


	if @switch>=1
		print @fullmsg;  
    if @switch>=2
		INSERT INTO dbo.Protocols	(occurredat, typeid, result, parameters) VALUES (GETDATE(), 201, 0, @fullmsg);
   
	RETURN 0;
END
GO
/****** Object:  Table [dbo].[Templates]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Templates](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](80) NOT NULL,
	[description] [text] NULL,
	[mask] [varchar](80) NULL,
	[priority] [int] NOT NULL,
	[parameters] [xml] NOT NULL,
	[partnerId] [int] NULL,
 CONSTRAINT [XPKTemplates] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[TranCount]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TranCount](
	[TranCount] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[usersAccessLogs]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[usersAccessLogs](
	[user_id] [bigint] NOT NULL,
	[ip] [nvarchar](8) NOT NULL,
	[time] [datetime] NOT NULL,
	[Time_FK] [datetime] NULL,
	[FK_time] [datetime] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[WriteOffTempKW]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WriteOffTempKW](
	[username] [nvarchar](32) NULL,
	[amount] [decimal](15, 2) NULL,
	[pubdate] [datetime] NULL,
	[userid] [int] NULL,
	[kwAccountId] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[WrongUsers]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WrongUsers](
	[username] [nvarchar](32) NULL,
	[oldmoney] [numeric](10, 2) NULL,
	[oldbonus] [numeric](10, 2) NULL,
	[newmoney] [decimal](15, 2) NULL,
	[newbonus] [decimal](15, 2) NULL,
	[userid] [int] NULL,
	[basicAccId] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[WrongUsersKW]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WrongUsersKW](
	[username] [nvarchar](32) NULL,
	[oldmoney] [numeric](10, 2) NULL,
	[oldbonus] [numeric](10, 2) NULL,
	[newmoney] [decimal](15, 2) NULL,
	[newbonus] [decimal](15, 2) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[zzgold_logs]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[zzgold_logs](
	[id] [int] NULL,
	[username] [nvarchar](32) NULL,
	[money_before] [numeric](10, 2) NULL,
	[money_after] [numeric](10, 2) NULL,
	[pubdate] [datetime] NULL,
	[remoteaddr] [nvarchar](8) NULL,
	[clientid] [int] NULL,
	[serviceid] [int] NULL,
	[bonus] [bit] NULL,
	[log_id] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[zzmoney]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[zzmoney](
	[username] [nvarchar](32) NULL,
	[money] [numeric](10, 2) NULL,
	[bonus] [numeric](10, 2) NULL,
	[casid] [int] NULL,
	[blocked] [bit] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[nivalusers]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[nivalusers](
	[user_id] [bigint] NULL,
	[username] [nvarchar](32) NULL,
	[password] [nvarchar](32) NULL,
	[salt] [nvarchar](16) NULL,
	[email] [nvarchar](64) NULL,
	[remote_addr] [nvarchar](8) NULL,
	[user_update] [datetime] NULL,
	[last_login] [datetime] NULL,
	[reg_date] [datetime] NULL,
	[subscribe] [datetime] NULL,
	[banned] [bit] NULL,
	[banned_description] [nvarchar](128) NULL,
	[eula] [bit] NULL,
	[birthday] [datetime] NULL,
	[gender] [nvarchar](1) NULL,
	[restricted_games] [nvarchar](255) NULL,
	[by_partner_id] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [users].[Passive]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [users].[Passive](
	[name] [nvarchar](80) NOT NULL,
	[createdat] [datetime] NOT NULL,
	[email] [varchar](80) NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[BillingVersion]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BillingVersion](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[occurredat] [datetime] NOT NULL,
	[Vers] [int] NULL,
	[Scr_param] [xml] NULL,
 CONSTRAINT [XPKBillingVersion] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[sp_perf_bonusMoneyReplenish]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_perf_bonusMoneyReplenish]
	@minuteInterval int
AS
BEGIN
	SELECT
		isnull(SUM(amount), 0) AS sum_amount
	FROM
		Operations
	WHERE
		[type] = 102 AND systemid = 1
		AND executedat >= DATEADD(mi, (-1 * @minuteInterval), GETDATE())
END
GO
/****** Object:  StoredProcedure [dbo].[sp_perf_kwBonusMoneyReplenish]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_perf_kwBonusMoneyReplenish]
	@minuteInterval int
AS
BEGIN
	select isnull(sum(o.amount), 0) as sum_amount from Operations o
	inner join UserServices u on o.destaccid = u.accountId
	where o.[type] = 102 and u.serviceid = 14 
	AND executedat >= DATEADD(mi, (-1 * @minuteInterval), GETDATE())
END
GO
/****** Object:  StoredProcedure [dbo].[sp_perf_realMoneyWriteOffs]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_perf_realMoneyWriteOffs]
	@minuteInterval int
AS
BEGIN
	SELECT
		isnull(SUM(w.amount), 0) AS sum_amount
	FROM
		Operations o
		inner join WriteOffsPaymentSystem w
		on o.id = w.operationId
	WHERE
		o.[type] = 201 AND paymentSystemId NOT IN (1, 2, 3, 4)
		AND executedat >= DATEADD(mi, (-1 * @minuteInterval), GETDATE())
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_checkPaymentSystems]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/04/28
-- Description:	
-- =============================================
CREATE PROCEDURE [dbo].[sp_rpt_checkPaymentSystems] 
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- payment system
	@paymentSystem VARCHAR(50)
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	DECLARE @monthYear VARCHAR(50);
	
	-- check parameters
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '2000/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2000/01/30 00:00');
	DECLARE @daysCount INT;
	SET @daysCount = CAST(@tdate - @fdate AS INT);
	
	--	create date groups table
	CREATE TABLE #DateGroups( id INT primary key, startDate DATETIME, finishDate DATETIME)

	DECLARE @i INT;
	DECLARE @newDate DATETIME;

	SET @i = 0;

	WHILE (@fDate < @tDate)
	BEGIN
		SET @newDate = dateadd(day, 1, @fDate);
		SET @i = @i + 1;
		IF (@newdate >= @tdate)
			SET @newdate = @tdate;

		INSERT INTO #DateGroups
		VALUES (@i, @fdate, @newdate) 

		SET @fDate = @newdate;
	END	
	
	SELECT startDate AS Date,
		amount AS Amount,
		dbo.sf_decimal_get_comission() AS Commission,
		(amount - dbo.sf_decimal_get_comission()) AS Transfers,
		0 AS Fact,
		executedat AS ComingDate,
		(amount - dbo.sf_decimal_get_comission() - 0) AS Delta		
	FROM dbo.Operations, dbo.PaymentSystems, #DateGroups
	WHERE type = '102' AND
		systemid = dbo.PaymentSystems.id AND
		dbo.PaymentSystems.name = @paymentSystem AND
		executedat BETWEEN startDate AND finishDate	
	ORDER BY executedat
		
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getGroupGamesSummary]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/06
-- Description:	Retrieves games summary by group id

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getGroupGamesSummary]
	-- session id
	@spid INT,
	-- group id, NULL for all groups
	@groupid INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
AS
BEGIN
	IF	OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL
	BEGIN
		RETURN SELECT NULL AS ServiceID, NULL AS ServiceName,NULL AS TotalAmount, NULL AS TransactionsCount;
	END	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
		
	
	-- main select
	SELECT OP.serviceid AS ServiceID, SV.name AS ServiceName, SUM(OP.amount) AS TotalAmount, COUNT(*) AS TransactionsCount 
		FROM dbo.Operations AS OP
		INNER JOIN dbo.Services AS SV ON OP.serviceid=SV.id
		INNER JOIN ##tmp_rptExpensesGames AS EG ON OP.serviceid = EG.serviceid
		INNER JOIN ##tmp_rptExpensesUsers AS EU ON OP.userid = EU.userid
		INNER JOIN ##tmp_rptExpensesSubjects AS ES ON CAST(OP.reason AS NVARCHAR(80)) = ES.reason
	
		WHERE OP.type = 201 
			AND OP.reason IS NOT NULL AND OP.serviceid IS NOT NULL
			AND ES.spid=@spid
			AND EG.spid=@spid
			AND EU.spid=@spid AND (@groupid IS NULL OR EU.groupid=@groupid)
			AND OP.executedat BETWEEN @fromDate AND @toDate
		GROUP BY OP.serviceid, SV.name
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getGroupPaymentSystemsSummary]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/10
-- Description:	Retrieves PS summary by group id

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getGroupPaymentSystemsSummary]
	-- session id
	@spid INT,
	-- group id, if there NULL == for all groups
	@groupid INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
AS
BEGIN
	IF	OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL
	BEGIN
		RETURN SELECT NULL AS PaymentSystem, NULL AS TotalAmount, NULL AS TransactionsCount ;
	END	
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
		
	
	-- main select
	SELECT PS.name AS PaymentSystem, SUM(TA.amount) AS TotalAmount, COUNT(TA.amount) AS TransactionsCount FROM dbo.Operations AS OP
	INNER JOIN dbo.Transactions AS TA ON OP.id=TA.operationid
	INNER JOIN dbo.SubAccounts AS SA ON TA.subaccid = SA.id
	INNER JOIN dbo.PaymentSystems AS PS ON SA.systemid=PS.id
	INNER JOIN ##tmp_rptExpensesGames AS EG ON OP.serviceid = EG.serviceid
	INNER JOIN ##tmp_rptExpensesUsers AS EU ON EU.userid = OP.userid
	INNER JOIN ##tmp_rptExpensesSubjects AS ES ON CAST(OP.reason AS NVARCHAR(80)) = ES.reason
	
	WHERE 
		type>=200 AND type<300  -- expenses
		AND OP.reason IS NOT NULL AND OP.serviceid IS NOT NULL
		AND ES.spid=@spid
		AND EG.spid=@spid
		AND EU.spid=@spid AND (@groupid IS NULL OR EU.groupid = @groupid)
		AND OP.executedat BETWEEN @fromDate AND @toDate
	GROUP BY PS.name
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getGroups]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/25
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getGroups]
	-- session id
	@spid INT = NULL
AS
BEGIN

	IF	OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL
	BEGIN
		RETURN SELECT NULL AS spid, NULL AS groupid, NULL AS start, NULL AS finish;
	END	
	
	SET FMTONLY OFF;

	SELECT * FROM ##tmp_rptExpensesGroups WHERE spid = @spid;
	

END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getGroupStatisticsByGroupID]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/10
-- Description:	Retrieves group statistics 

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getGroupStatisticsByGroupID]
	-- session id
	@spid INT,
	-- group id
	@groupID INT,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
	
AS
BEGIN
	IF	OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL
	BEGIN
		SELECT NULL AS GroupCountPercent, NULL AS TotalAmountPercent, NULL AS TransactionsCountPercent;
	END	

	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)


	DECLARE @groupCount AS DECIMAL;
	DECLARE @count AS DECIMAL;

	DECLARE @totalAmountGroup AS DECIMAL;
	DECLARE @totalAmount AS DECIMAL;

	DECLARE @transactionCountGroup AS DECIMAL;
	DECLARE @transactionCount AS DECIMAL;

	-- calculate the number of users in this group
	SELECT @groupCount=COUNT(userid) 
	FROM ##tmp_rptExpensesUsers WHERE groupid=@groupID AND periodid=1 AND spid=@spid;

	-- calculate the number of users in all groups
	SELECT @count=COUNT(userid)
	FROM ##tmp_rptExpensesUsers WHERE periodid=1 AND spid=@spid;

	-- calculate the percent of total amount of expenses for group
	SELECT @totalAmountGroup=SUM(TA.amount), @transactionCountGroup=COUNT(TA.amount) FROM dbo.Operations AS OP
		INNER JOIN dbo.Transactions AS TA ON OP.id=TA.operationid
		INNER JOIN dbo.SubAccounts AS SA ON TA.subaccid = SA.id
		INNER JOIN dbo.PaymentSystems AS PS ON SA.systemid=PS.id
		WHERE type>=200 AND type<300 
			AND CAST(OP.reason AS NVARCHAR(80)) IN (SELECT reason FROM ##tmp_rptExpensesSubjects  WHERE spid=@spid)
			AND OP.serviceid IN (SELECT serviceid FROM ##tmp_rptExpensesGames  WHERE spid=@spid)
			AND OP.executedat BETWEEN @fromDate AND @toDate
			AND OP.userid IN (SELECT userid FROM ##tmp_rptExpensesUsers 
								WHERE spid=@spid AND groupid=@groupID);
	
	-- calculate the percent of total amount of expenses for all groups
	SELECT @totalAmount=SUM(TA.amount), @transactionCount=COUNT(TA.amount) FROM dbo.Operations AS OP
		INNER JOIN dbo.Transactions AS TA ON OP.id=TA.operationid
		INNER JOIN dbo.SubAccounts AS SA ON TA.subaccid = SA.id
		INNER JOIN dbo.PaymentSystems AS PS ON SA.systemid=PS.id
		WHERE type>=200 AND type<300 
			AND CAST(OP.reason AS NVARCHAR(80)) IN (SELECT reason FROM ##tmp_rptExpensesSubjects  WHERE spid=@spid)
			AND OP.serviceid IN (SELECT serviceid FROM ##tmp_rptExpensesGames  WHERE spid=@spid)
			AND OP.executedat BETWEEN @fromDate AND @toDate
			AND OP.userid IN (SELECT userid FROM ##tmp_rptExpensesUsers 
								WHERE spid=@spid);
			
							
	IF(@transactionCountGroup IS NULL)
		SET @transactionCountGroup=0;
	IF(@totalAmountGroup IS NULL)
		SET @totalAmountGroup=0;
	IF(@groupCount IS NULL)
		SET @groupCount=0;

	
	SELECT CASE WHEN @count<>0 THEN @groupCount/@count*100 ELSE 0 END AS GroupCountPercent, 
		CASE WHEN @totalAmount<>0 THEN @totalAmountGroup/@totalAmount*100 ELSE 0 END AS TotalAmountPercent,
		CASE WHEN @transactionCount<>0 THEN  @transactionCountGroup/@transactionCount*100 ELSE 0 END AS TransactionsCountPercent
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getGroupStuffPercent]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/10
-- Description:	Retrieves stuff statistics 

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getGroupStuffPercent]
	-- session id
	@spid INT,
	-- group id
	@groupID INT
AS
BEGIN
	IF OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL
	BEGIN
		RETURN SELECT NULL AS OldGroup, NULL AS PercentStuff
	END	

	DECLARE @groupCount AS DECIMAL
	-- calculate the number of users in this group
	SELECT @groupCount=COUNT(userid) 
		FROM ##tmp_rptExpensesUsers WHERE groupid=@groupID AND periodid=1 AND spid=@spid;

	IF @groupCount<>0
	BEGIN
		SELECT PUO.groupid AS OldGroup, COUNT(*)*100/@groupCount AS PercentStuff
		FROM  ##tmp_rptExpensesUsers AS PUN
		INNER JOIN ##tmp_rptExpensesUsers AS PUO ON PUN.userid = PUO.userid
		WHERE
			PUN.spid=@spid AND PUO.spid=@spid 
			AND PUN.periodid = 1 AND PUO.periodid = 0	
			AND PUN.groupid = @groupID
		GROUP BY PUO.groupid 
	END
	ELSE
		RETURN
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getGroupSubjectsSummary]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/10
-- Description:	Retrieves subjects summary by group id

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getGroupSubjectsSummary]
	-- session id
	@spid INT,
	-- group id. if == NULL - for all groups
	@groupid INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
AS
BEGIN
	IF	OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL OR 
		OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL
	BEGIN
		RETURN SELECT NULL AS Subject, NULL AS TotalAmount, NULL AS TransactionsCount;
	END	
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
		
	
	-- main select
	SELECT	CAST(OP.reason AS NVARCHAR(80)) AS Subject, 
			SUM(OP.amount) AS TotalAmount, 
			COUNT(*) AS TransactionsCount 
		FROM dbo.Operations AS OP
		INNER JOIN ##tmp_rptExpensesGames AS EG ON OP.serviceid = EG.serviceid
		INNER JOIN ##tmp_rptExpensesUsers AS EU ON OP.userid = EU.userid
		INNER JOIN ##tmp_rptExpensesSubjects AS ES ON CAST(OP.reason AS NVARCHAR(80)) = ES.reason
	
		WHERE type>=200 AND type<300 
			AND OP.reason IS NOT NULL AND OP.serviceid IS NOT NULL
			AND ES.spid=@spid
			AND EG.spid=@spid
			AND EU.spid=@spid AND EU.periodid=1 AND ( @groupid IS NULL OR EU.groupid=@groupid)
			AND OP.executedat BETWEEN @fromDate AND @toDate
		GROUP BY CAST(OP.reason AS NVARCHAR(80))	
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getGroupTransactions]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/07
-- Description:	Retrieves users by group id

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getGroupTransactions]
	-- spid
	@spid INT,
	-- group id. if == NULL - for all groups
	@groupID INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
	
AS
BEGIN
	IF	OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL OR
		OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL OR
		OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL
	BEGIN
		RETURN;
	END	
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
	
	
	-- main select
	SELECT US.name, CAST(OP.reason AS NVARCHAR(80)) AS Subject, OP.amount AS Amount 
	FROM dbo.Operations AS OP
		INNER JOIN dbo.Users AS US ON OP.userid=US.id
		INNER JOIN ##tmp_rptExpensesGames AS EG ON OP.serviceid = EG.serviceid
		INNER JOIN ##tmp_rptExpensesUsers AS EU ON OP.userid = EU.userid
		INNER JOIN ##tmp_rptExpensesSubjects AS ES ON CAST(OP.reason AS NVARCHAR(80)) = ES.reason
		WHERE OP.type = 201 
			AND OP.reason IS NOT NULL AND OP.serviceid IS NOT NULL
			AND ES.spid=@spid
			AND EG.spid=@spid
			AND EU.spid=@spid AND EU.periodid=1 AND (@groupid IS NULL OR EU.groupid=@groupid)
			AND OP.executedat BETWEEN @fromDate AND @toDate
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_getUsersByGroupID]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/07
-- Description:	Retrieves users by group id

CREATE PROCEDURE [dbo].[sp_rpt_expenses_getUsersByGroupID]
	-- spid
	@spid INT,
	-- group id. if == NULL - for all groups
	@groupID INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
	
AS
BEGIN
	IF	OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL OR
		OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL OR
		OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL
	BEGIN
		RETURN;
	END	
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
	
	
	-- main select
	SELECT US.name, CAST(OP.reason AS NVARCHAR(80)) AS Subject, OP.amount AS Amount 
	FROM dbo.Operations AS OP
		INNER JOIN dbo.Users AS US ON OP.userid=US.id
		INNER JOIN ##tmp_rptExpensesGames AS EG ON OP.serviceid = EG.serviceid
		INNER JOIN ##tmp_rptExpensesUsers AS EU ON OP.userid = EU.userid
		INNER JOIN ##tmp_rptExpensesSubjects AS ES ON CAST(OP.reason AS NVARCHAR(80)) = ES.reason
		WHERE OP.type = 201 
			AND OP.reason IS NOT NULL AND OP.serviceid IS NOT NULL
			AND ES.spid=@spid
			AND EG.spid=@spid
			AND EU.spid=@spid AND (@groupid IS NULL OR EU.groupid=@groupid)
			AND OP.executedat BETWEEN @fromDate AND @toDate
END
GO
/****** Object:  StoredProcedure [dbo].[a11111tezzd]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[a11111tezzd] 
	-- Add the parameters for the stored procedure here
	
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	print 'Tezzd tezzd tezzzzzzd...66666'
END
GO
/****** Object:  Table [dbo].[Protocols]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Protocols](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[occurredat] [datetime] NOT NULL,
	[typeid] [int] NOT NULL,
	[userid] [int] NULL,
	[empid] [int] NULL,
	[operationid] [int] NULL,
	[serviceid] [int] NULL,
	[systemid] [int] NULL,
	[amount] [decimal](15, 2) NULL,
	[result] [int] NULL,
	[parameters] [text] NULL,
 CONSTRAINT [XPKProtocols] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getExpensesByGames]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/05/03
-- Description:	Retrieves expenses by games
-- =============================================
CREATE PROCEDURE [dbo].[sp_rpt_getExpensesByGames]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
	
AS
BEGIN

	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	IF @fromDate IS NULL
		SELECT @fromDate = CONVERT(DATETIME, '2000/01/01 00:00');
	
	IF @toDate IS NULL
		SELECT @toDate = CONVERT(DATETIME, '2100/01/01 00:00');	
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	


	--	create date groups table
	CREATE TABLE #DateGroups( startDate DATETIME, finishDate DATETIME, monthName VARCHAR(50))

	DECLARE @i INT;
	DECLARE @newDate DATETIME;

	SET @i = 0;

	WHILE (@fDate < @tDate)
	BEGIN
		SET @newDate = dateadd(day, 1, @fDate);
		SET @i = @i + 1;
		IF (@newdate >= @tdate)
			SET @newdate = @tdate;

		INSERT INTO #DateGroups
		VALUES ( @fdate, @newdate, DATENAME(day, @fdate)) 

		SET @fDate = @newdate;
	END
	
	DECLARE @sum FLOAT;
	SELECT @sum = SUM(amount) 
	FROM dbo.Operations, #DateGroups	
	WHERE type = '201' AND
		executedat BETWEEN startDate AND finishDate

	SELECT 
		startDate AS Date,
		name AS GameName, 
		SUM(amount) AS Amount,
		(SUM(amount) * 100 / @sum ) AS AmountPct
	FROM dbo.Operations, dbo.Services, #DateGroups 
	WHERE type = '201' AND
		dbo.Operations.serviceid = dbo.Services.id AND
		executedat BETWEEN startDate AND finishDate	  
	GROUP BY dbo.Services.id, name, startDate;

END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getExpensesByGames_trends]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/04/28
-- Description:	Retrieves expenses by month
-- =============================================
CREATE PROCEDURE [dbo].[sp_rpt_getExpensesByGames_trends] 
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	DECLARE @monthYear VARCHAR(50);
	
	-- check parameters
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF @fDate IS NULL
		SELECT @fDate = CONVERT(DATETIME, '2000/04/01 00:00');
	
	IF @fDate IS NULL
		SELECT @tDate = CONVERT(DATETIME, '2000/04/30 00:00');	

	DECLARE @daysCount INT;
	SET @daysCount = CAST(@tdate - @fdate AS INT);
	
	--	create date groups table
	CREATE TABLE #DateGroups( id INT primary key, startDate DATETIME, finishDate DATETIME)

	DECLARE @i INT;
	DECLARE @newDate DATETIME;

	SET @i = 0;

	WHILE (@fDate < @tDate)
	BEGIN
		SET @newDate = dateadd(day, 1, @fDate);
		SET @i = @i + 1;
		IF (@newdate >= @tdate)
			SET @newdate = @tdate;

		INSERT INTO #DateGroups
		VALUES (@i, @fdate, @newdate) 

		SET @fDate = @newdate;
	END

	DECLARE @start DATETIME;
	SET @start = (SELECT TOP(1) startDate FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate ORDER BY startDate);
	
	--AmountPerDay
	CREATE TABLE #TMP_DATA(X FLOAT, Y FLOAT);
	INSERT INTO #TMP_DATA
		SELECT  CAST(startDate - @start AS DECIMAL) AS X, 
			(SELECT SUM(dbo.Operations.amount)) AS Y
			--(SELECT SUM(dbo.Operations.amount)/@daysCount) AS Y
		FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate;	
	CREATE TABLE #amountPerDayTable (X FLOAT, Y FLOAT, YL FLOAT);
	INSERT #amountPerDayTable EXEC dbo.sp_int_linear_approximation;
	
	DELETE FROM #TMP_DATA;
	--CountPerDay
	INSERT INTO #TMP_DATA
		SELECT  CAST(startDate - @start AS DECIMAL) AS X, 
			(SELECT COUNT(dbo.Operations.amount)) AS Y
			--(SELECT COUNT(dbo.Operations.amount)/@daysCount) AS Y 
		FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate
	CREATE TABLE #countPerDayTable (X FLOAT, Y FLOAT, YL FLOAT);
	INSERT #countPerDayTable EXEC dbo.sp_int_linear_approximation;
	
	--avAmountOP
	DELETE FROM #TMP_DATA;
	INSERT INTO #TMP_DATA
		SELECT  CAST(startDate - @start AS DECIMAL) AS X, 
			(SELECT SUM(dbo.Operations.amount)/COUNT(dbo.Operations.amount)) AS Y
		FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate
	CREATE TABLE #avAmountTable (X FLOAT, Y FLOAT, YL FLOAT);
	INSERT #avAmountTable EXEC dbo.sp_int_linear_approximation;
	
	--	create result request
	SELECT  startDate AS executeDate,
		--SUM(dbo.Operations.amount) AS AmountOP, 
		--COUNT(dbo.Operations.amount) AS CountOP,
		#amountPerDayTable.Y AS AmountPerDay,
		#amountPerDayTable.YL AS AmountPerDayTrend,
		#countPerDayTable.Y AS CountPerDay,
		#countPerDayTable.YL AS CountPerDayTrend,
		#avAmountTable.Y AS avAmountOP,
		#avAmountTable.YL AS avAmountOPTrend
	FROM dbo.Operations, #DateGroups, #amountPerDayTable, #countPerDayTable, #avAmountTable
	WHERE type = '201' AND
		executedat BETWEEN startDate AND finishDate AND
		#amountPerDayTable.X = CAST(startDate - @start AS DECIMAL) AND 
		#countPerDayTable.X = CAST(startDate - @start AS DECIMAL) AND 
		#avAmountTable.X = CAST(startDate - @start AS DECIMAL)
	GROUP BY startDate, #amountPerDayTable.YL, #avAmountTable.YL, #countPerDayTable.YL, #amountPerDayTable.Y, #avAmountTable.Y, #countPerDayTable.Y
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getExpensesByMonth]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/04/28
-- Description:	Retrieves expenses by month
-- =============================================
CREATE PROCEDURE [dbo].[sp_rpt_getExpensesByMonth] 
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	DECLARE @monthYear VARCHAR(50);
	
	-- check parameters
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');

	--	create date groups table
	CREATE TABLE #DateGroups( id INT primary key, startDate DATETIME, finishDate DATETIME, monthName VARCHAR(50), daysCount INT)

	DECLARE @i INT;
	DECLARE @newDate DATETIME;

	SET @i = 0;

	WHILE (@fDate < @tDate)
	BEGIN
		SET @newDate = dateadd(month, 1, @fDate);
		SET @i = @i + 1;
		IF (@newdate >= @tdate)
			SET @newdate = @tdate;

		INSERT INTO #DateGroups
		VALUES (@i, @fdate, @newdate, DATENAME(month, @fdate), CAST(@newdate - @fdate AS INT)) 

		SET @fDate = @newdate;
	END
	
	DECLARE @start DATETIME;
	SET @start = (SELECT TOP(1) startDate FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate ORDER BY startDate);
	
	--AmountOP
	CREATE TABLE #TMP_DATA(X FLOAT, Y FLOAT);
	INSERT INTO #TMP_DATA
		SELECT  CAST(startDate - @start AS DECIMAL) AS X,
			SUM(dbo.Operations.amount) AS Y 
		FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate
	CREATE TABLE #AmountOPTable (X FLOAT, Y FLOAT, YL FLOAT);
	INSERT #AmountOPTable EXEC dbo.sp_int_linear_approximation;	
	
	DELETE FROM #TMP_DATA;
	--CountOP
	INSERT INTO #TMP_DATA
		SELECT  CAST(startDate - @start AS DECIMAL) AS X,
			COUNT(dbo.Operations.amount) AS Y 
		FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate
	CREATE TABLE #CountOPTable (X FLOAT, Y FLOAT, YL FLOAT);
	INSERT #CountOPTable EXEC dbo.sp_int_linear_approximation;	
	
	DELETE FROM #TMP_DATA;
	--AmountAVG
	INSERT INTO #TMP_DATA
		SELECT  CAST(startDate - @start AS DECIMAL) AS X,
			(SELECT SUM(dbo.Operations.amount)/COUNT(dbo.Operations.amount)) AS Y 
		FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate
	CREATE TABLE #AmountAVGTable (X FLOAT, Y FLOAT, YL FLOAT);
	INSERT #AmountAVGTable EXEC dbo.sp_int_linear_approximation;
	
	DELETE FROM #TMP_DATA;
	--AmountPerDay
	INSERT INTO #TMP_DATA
		SELECT  CAST(startDate - @start AS DECIMAL) AS X,
			(SELECT SUM(dbo.Operations.amount)/daysCount) AS Y 
		FROM dbo.Operations, #DateGroups
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate
		GROUP BY startDate, daysCount
	CREATE TABLE #AmountPerDayTable (X FLOAT, Y FLOAT, YL FLOAT);
	INSERT #AmountPerDayTable EXEC dbo.sp_int_linear_approximation;
		
	--	create result request
	SELECT  (#DateGroups.monthName) AS monthName, 
			DATEPART("yyyy", startDate) AS yearName,
			startDate AS startDate,
			#AmountOPTable.Y AS AmountOP, 
			#AmountOPTable.YL AS AmountOPTrend,
			#CountOPTable.Y AS CountOP,
			#CountOPTable.YL AS CountOPTrend,
			#AmountAVGTable.Y AS AmountAVG,
			#AmountAVGTable.YL AS AmountAVGTrend,
			#AmountPerDayTable.Y AS AmountPerDay,
			#AmountPerDayTable.YL AS AmountPerDayTrend,
			(SELECT COUNT(dbo.Operations.amount)/daysCount) AS CountPerDay
		FROM dbo.Operations, #DateGroups, #AmountAVGTable, #AmountOPTable, #AmountPerDayTable, #CountOPTable
		WHERE type = '201' AND
			executedat BETWEEN startDate AND finishDate AND
			#AmountAVGTable.X = CAST(startDate - @start AS DECIMAL) AND 
			#AmountOPTable.X = CAST(startDate - @start AS DECIMAL) AND 
			#AmountPerDayTable.X = CAST(startDate - @start AS DECIMAL) AND
			#CountOPTable.X = CAST(startDate - @start AS DECIMAL)
		
		GROUP BY monthName, daysCount, startDate, #AmountOPTable.Y, #AmountOPTable.YL, #CountOPTable.Y, #CountOPTable.YL, #AmountPerDayTable.Y, #AmountPerDayTable.YL, #AmountAVGTable.Y, #AmountAVGTable.YL
		ORDER BY startDate

END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_confirmWriteOff]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_confirmWriteOff]
	@reserveId int,
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	declare @svcId int;
	declare @userId int;
	declare @accountId int;
	declare @amount decimal;
	declare @reason nvarchar(max);
	declare @cbt bit;
	declare @finishTime datetime;
	declare @OPERID int;

    -- check parameters
	IF @reserveId IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
	-- resolve reserveId
	IF @ERROR = 0
	BEGIN
		SELECT 	@svcId = svcId, @userId = userId, @accountId = accountId, @amount = amount, 
						@reason = reason, @cbt = cbt, @finishTime = finishTime
		FROM WriteOffreserve WHERE id = @reserveId;
		IF @cbt IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_RESERVE');
	END

	IF @error <> 0
		RETURN -1;
	
	BEGIN TRAN ConfirmReserve 
	
	delete from WriteOffReserve where id = @reserveId;

	IF @finishTime > GETDATE()
	BEGIN
		EXEC DBO.sp_int_writeoff @svcId, @userId, @accountId, @amount, 201, @reason, @cbt, @OPERID OUTPUT, @error OUTPUT
		IF  @ERROR = 0
			IF (@@TRANCOUNT > 0) COMMIT TRAN ConfirmReserve
		ELSE
			IF (@@TRANCOUNT > 0) ROLLBACK TRAN ConfirmReserve
	END
	ELSE
	BEGIN
		IF (@@TRANCOUNT > 0) COMMIT TRAN ConfirmReserve
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OBSOLETE_RESERVE');
		RETURN -1;
	END

	-- log request ============================================================================	
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@userId='  + cast(@userid as nvarchar(11)) + 
		':@reserveId=' + cast(@reserveId as nvarchar(11)) + 
		':@account='  + CASE WHEN @accountId IS NULL THEN 'null' ELSE cast(@accountId as varchar(50)) END +
		':@reason='  + cast(@reason as VARCHAR(2000));
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 503, @serviceid=@svcid, @userid = @userid, @operationid = @OPERID, 
		@amount = @amount, @parameters = @content, @result = @error, @error = @errlog OUTPUT
	-- end log request ============================================================================	

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_createUser]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_createUser]
	-- user name
	@name varchar(80),
	-- e-mail
	@email varchar(80),
	-- password
	@password varbinary(80),
	-- referal code, can be NULL
	@referal varchar(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	DECLARE @err_int int;

	SET NOCOUNT ON;
	
	DECLARE @ACCID INT;
	DECLARE @PROGRAMID INT;
	DECLARE @TEMPLATEID INT;
	DECLARE @USERID INT

	SET @ERROR = 0;

	-- check parameters
    IF @NAME IS NULL OR @EMAIL IS NULL OR @PASSWORD IS NULL
	BEGIN
		SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END

	-- check existing of user with the same name
	IF @ERROR = 0
	BEGIN
		IF	EXISTS (SELECT ID FROM USERS WHERE NAME = @name)
			SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_USER_EXISTS');
	END
	
	IF @ERROR = 0
	BEGIN
		-- create new user
		BEGIN TRANSACTION CREATEUSER
		-- resolve partner program
		SET @PROGRAMID = DBO.SF_INT_RESOLVE_PARTNER_PROGRAM(@REFERAL);
		
		-- check existing of user with the same e-mail
		IF	EXISTS (SELECT USERID FROM dbo.Profiles, dbo.Users 
					WHERE email = @email AND ISNULL(partnerid,0) = ISNULL(@PROGRAMID,0) AND userid = id)
			SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_EMAIL_EXISTS');

		-- resolve template
		SET @TEMPLATEID = DBO.SF_INT_RESOLVE_TEMPLATE(@REFERAL);
		-- insert main record
		IF @ERROR = 0
		BEGIN TRY
			DECLARE @resTbl table(id int NOT NULL);
			
			INSERT INTO dbo.users (name, password, accid, partnerid)
				OUTPUT INSERTED.id
				INTO @resTbl
			VALUES (@name, @password, @accid, @programid);
			
			SELECT TOP 1 @USERID = id FROM @resTbl;
		END TRY
		BEGIN CATCH						
			SET @err_int = ERROR_NUMBER();			
			EXEC dbo.sp_int_trace 'Unable to create new user', @err_int;			
			SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
		END CATCH
		
		-- create new account
		IF @ERROR= 0
		BEGIN TRY
			EXECUTE @ACCID = DBO.SP_INT_CREATE_ACCOUNT @userid = @USERID;				
			IF @ACCID IS NULL
			BEGIN
				EXEC dbo.sp_int_trace 'Unable to create new account';
				SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
			END			
		END TRY			
		BEGIN CATCH
			EXEC dbo.sp_int_trace 'Unable to create new account';
			SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
		END CATCH
		
		-- update user info
		IF @ERROR= 0
		BEGIN TRY
			UPDATE dbo.Users SET accid = @ACCID WHERE id= @USERID;
		END TRY
		BEGIN CATCH
			SET @err_int = ERROR_NUMBER();			
			EXEC dbo.sp_int_trace 'Unable to create new user', @err_int;			
			SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
		END CATCH
		
		-- insert profile info record
		IF @ERROR= 0
		BEGIN TRY
			INSERT INTO	DBO.PROFILES (USERID, CREATEDAT, REFERALCODE, EMAIL, TEMPLATEID, AGREEMENT)
				VALUES (@USERID, GETDATE(), @REFERAL, @EMAIL,  @TEMPLATEID, 0);
		END TRY
		BEGIN CATCH
			SET @err_int = ERROR_NUMBER();			
			EXEC dbo.sp_int_trace 'Unable to create new user', @err_int;			
			SET @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');	
		END CATCH
		
		IF @ERROR = 0
			COMMIT TRANSACTION CREATEUSER;
		ELSE
			ROLLBACK TRANSACTION CREATEUSER;
	END

	-- log request ================================================================================
	DECLARE @errlog INT; 
	SET @errlog = 0;
	
	EXEC dbo.sp_log_createUser @name = @name, @email = @email, @password = @password, @referal = @referal,
		 @userid = @USERID, @partnerid = @PROGRAMID, @templateid = @TEMPLATEID, @state = @error,  @error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================
		
	IF @ERROR <> 0
		RETURN -1;
	
	SELECT userid AS ID, dbo.Accounts.name AS ACCOUNT FROM dbo.Accounts WHERE id = @ACCID;
	
	RETURN 0;
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getAwardAmount]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getAwardAmount]
	@user varchar(80),
    @svcid    int,
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	SET NOCOUNT ON;
	
	DECLARE @USERID INT;
	declare @partnerId int
    DECLARE @awardpsid INT;
	SELECT @awardpsid = dbo.sf_int_get_award_ps();
	declare @mainAccId int

	DECLARE @awardAmount DECIMAL(15, 2);
	
	IF (@USER IS NULL)
	BEGIN --общий баланс awardMoney
		select @awardAmount = SUM(amount) FROM dbo.SubAccounts 
				WHERE systemId = @awardpsid

		IF @awardAmount IS NULL
			SET @awardAmount = 0;
		SELECT @awardAmount AS AwardAmount;
		return 0;
	END
	ELSE --award баланс юзера на всех счетах 
	BEGIN
		-- resolve user id
		IF @ERROR = 0
		BEGIN
			SELECT @USERID = ID, @mainAccId = accid FROM USERS WHERE USERS.NAME = @USER;
			IF @USERID IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		END

		IF @error <> 0
		RETURN -1;

		select @awardAmount = SUM(amount) FROM dbo.SubAccounts 
				WHERE systemId = @awardpsid	and accid in
					(select @mainAccId union select accountid from UserServices where userid = @USERID)	

		IF @awardAmount IS NULL
			SET @awardAmount = 0;
		
		SELECT @awardAmount AS AwardAmount;

		RETURN 0;
	END
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getRegistrationCount]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/26
-- Description:	Retrieves count of registrations

CREATE PROCEDURE [dbo].[sp_rpt_getRegistrationCount]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	
    
		SELECT COUNT(*) AS Registartions FROM dbo.Protocols 
		WHERE typeid = 502 AND result = 0  AND occurredat BETWEEN @fDate AND @tDate
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getOperationDetails]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getOperationDetails]
	@user varchar(80),
	@opId int,
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT @error = 0;
	
	DECLARE @USERID INT;

    -- check parameters
	IF @USER IS NULL OR @opId IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END
	
	IF @ERROR = 0
	BEGIN
		SELECT 
			o.id AS operationId,
			w.paymentSystemId,
			w.amount,
			o.userid,
			o.serviceid
		FROM 
			Operations AS o 
			INNER JOIN WriteOffsPaymentSystem AS w ON w.operationId = o.id 
		WHERE 
			o.userid = @USERID AND o.type = 201 AND o.id = @opId;
			
		RETURN 0;
	END
	
	RETURN -1;	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getUniquePaidUsersCount]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/26
-- Description:	Retrieves count of game logins

CREATE PROCEDURE [dbo].[sp_rpt_getUniquePaidUsersCount]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	SELECT COUNT(DISTINCT userid) AS UsersCount FROM dbo.Operations
		WHERE type>=100 AND type<200 AND systemid<>1 AND systemid<>2
		AND executedat BETWEEN @fromDate AND @toDate
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getCountPercentByGroupID]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/29
-- Description:	Процент относительно общего количества пользователей за период

CREATE PROCEDURE [dbo].[sp_rpt_payments_getCountPercentByGroupID]
	-- session id
	@spid INT,
	-- group id
	@groupID INT
	
AS
BEGIN
	IF OBJECT_ID('tempdb..##tmp_rptPaymentsMain') is NULL
	BEGIN
		RETURN;
	END	
	DECLARE @procent AS DECIMAL(15,2)
	DECLARE @groupCount AS DECIMAL(15,2)
	DECLARE @totalCount AS DECIMAL(15,2)

	SELECT @groupCount=COUNT(*) FROM ##tmp_rptPaymentsMain WITH(NOLOCK) WHERE groupId=@groupID AND spid=@spid
	SELECT @totalCount=COUNT(*) FROM ##tmp_rptPaymentsMain WITH(NOLOCK) WHERE spid=@spid
	
	IF (@totalCount=0)
		SET @procent=0;
		ELSE SET @procent=@groupCount/@totalCount*100
	SELECT @procent AS StuffPercent; 
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getGroupGamesSummary]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/12
-- Description:	Group games statistic

CREATE PROCEDURE [dbo].[sp_rpt_payments_getGroupGamesSummary]
	-- session id
	@spid INT,
	-- group id
	@groupid INT,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
AS
BEGIN
	IF OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL
	BEGIN
		--SELECT NULL AS ServiceID, NULL AS ServiceName, NULL AS TotalAmount, NULL AS TransactionsCount
		RETURN 0;
	END	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
	
	
	-- main select
	SELECT OP.serviceid AS ServiceID, SV.name AS ServiceName,SUM(OP.amount) AS TotalAmount, COUNT(OP.amount) AS TransactionsCount 
		FROM dbo.Operations AS OP WITH(NOLOCK)
		INNER JOIN dbo.Services AS SV WITH(NOLOCK) ON OP.serviceid=SV.id
		INNER JOIN ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK) ON OP.userid = PU.userid
	WHERE type>=200 AND type<300 
		AND PU.spid = @spid AND (@groupid IS NULL OR PU.groupid = @groupid)  AND PU.periodid = 1
		AND OP.reason IS NOT NULL AND OP.serviceid IS NOT NULL
		AND OP.executedat BETWEEN @fromDate AND @toDate
	GROUP BY OP.serviceid, SV.name
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getGroupPayments]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/29
-- Update 1: 2010/05/10
-- Description:	Retrieves users by session id and group id

CREATE PROCEDURE [dbo].[sp_rpt_payments_getGroupPayments]
	-- session id
	@spid INT,
	-- group id, NULL for all groups
	@groupId INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL

AS
BEGIN
	IF	OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL OR
		OBJECT_ID('tempdb..##tmp_rptPaymentsSystems') is NULL
	BEGIN
		SELECT NULL AS name, NULL AS Amount, NULL AS executedat, NULL AS PaymentSytem 
		RETURN 0;
	END	
	
	-- 3. check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
	
	
	-- main select
	SELECT US.name,OP.amount AS Amount, OP.executedat, PS.name AS PaymentSytem 
		FROM dbo.Operations AS OP WITH(NOLOCK)
		INNER JOIN dbo.Users AS US WITH(NOLOCK) ON OP.userid=US.id
		INNER JOIN dbo.PaymentSystems AS PS WITH(NOLOCK) ON OP.systemid=PS.id
		INNER JOIN ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK) ON OP.userid = PU.userid
		INNER JOIN ##tmp_rptPaymentsSystems AS TPS WITH(NOLOCK) ON OP.systemid = TPS.systemid
	
	WHERE 
		type>=100 AND type<200 
		AND PU.spid=@spid AND (@groupid IS NULL OR PU.groupid=@groupid) AND PU.periodid = 1
		AND TPS.spid=@spid 
		AND OP.executedat BETWEEN @fromDate AND @toDate
	
	/*SELECT US.name,OP.amount AS Amount, OP.executedat, PS.name AS PaymentSytem 
		FROM dbo.Operations AS OP WITH(NOLOCK)
		INNER JOIN dbo.Users AS US WITH(NOLOCK) ON OP.userid=US.id
		INNER JOIN dbo.PaymentSystems AS PS WITH(NOLOCK) ON OP.systemid=PS.id
	WHERE 
		type>=100 AND type<200 
		AND OP.userid IN (SELECT userid FROM ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK)WHERE PU.spid=@spid AND (@groupid IS NULL OR PU.groupid=@groupid) AND PU.periodid = 1)
		AND OP.systemid IN (SELECT systemid FROM ##tmp_rptPaymentsSystems AS TPS WITH(NOLOCK) WHERE TPS.spid=@spid)
		AND OP.executedat BETWEEN @fromDate AND @toDate*/
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getGroupSubjectStatistic]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/30
-- Description:	Group games statistic

CREATE PROCEDURE [dbo].[sp_rpt_payments_getGroupSubjectStatistic]
	-- session id
	@spid INT,
	-- group id
	@groupID INT,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
AS
BEGIN
	IF OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL 
	BEGIN
		SELECT NULL AS Subject, NULL AS TotalAmount, NULL AS TransactionsCount FROM dbo.Operations AS OP
		RETURN;
	END
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
	
	
	-- main select
	SELECT CAST(OP.reason AS VARCHAR(MAX)) AS Subject, SUM(OP.amount) AS TotalAmount, COUNT(OP.amount) AS TransactionsCount 
		FROM dbo.Operations AS OP WITH(NOLOCK)
		INNER JOIN dbo.Services AS SV WITH(NOLOCK) ON OP.serviceid=SV.id
		INNER JOIN ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK) ON OP.userid = PU.userid
	WHERE type>=200 AND type<300 
		AND PU.spid = @spid AND (@groupid IS NULL OR PU.groupid = @groupid)  AND PU.periodid = 1
		AND OP.reason IS NOT NULL AND OP.serviceid IS NOT NULL
		AND OP.executedat BETWEEN @fromDate AND @toDate
	GROUP BY CAST(OP.reason AS VARCHAR(MAX))
	
	/*SELECT CAST(OP.reason AS VARCHAR(MAX)) AS Subject, SUM(OP.amount) AS TotalAmount, COUNT(OP.amount) AS TransactionsCount 
		FROM dbo.Operations AS OP WITH(NOLOCK)
		INNER JOIN dbo.Services AS SV WITH(NOLOCK) ON OP.serviceid=SV.id
	WHERE 
		type>=100 AND type<200 
		AND OP.userid IN (SELECT userid FROM ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK)WHERE PU.spid=@spid AND (@groupid IS NULL OR PU.groupid=@groupid) AND PU.periodid = 1)
		AND OP.systemid IN (SELECT systemid FROM ##tmp_rptPaymentsSystems AS TPS WITH(NOLOCK) WHERE TPS.spid=@spid)
		AND OP.executedat BETWEEN @fromDate AND @toDate
	GROUP BY CAST(OP.reason AS VARCHAR(MAX))*/	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getLoginCountByGroupID]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/30
-- Update 1:    2010/05/10
-- Description:	Retrieves count of game logins

CREATE PROCEDURE [dbo].[sp_rpt_payments_getLoginCountByGroupID]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- group id
	@groupID INT,
	-- session id
	@spid INT
AS
BEGIN
	IF OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL
	BEGIN
		RETURN;
	END	
	
	
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	SELECT SV.name AS ServiceName, COUNT(PC.serviceid)AS LoginCount  
		FROM Protocols AS PC WITH(NOLOCK)
		INNER JOIN dbo.Services AS SV WITH(NOLOCK) ON PC.serviceid=SV.id
		INNER JOIN ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK) ON PC.userid = PU.userid 
	WHERE typeid=501 
		AND PU.spid = @spid AND PU.periodid = 1 AND PU.groupId=@groupID
		AND result=0 
		AND occurredat BETWEEN @fDate AND @tDate 
	GROUP BY SV.name 
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_promoActivate]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_promoActivate]
	-- caller service id
	@svcid	int,
	-- user name
	@user varchar(80),
	-- account name. can be null. in this case acount of user-service subscription will be used
	@account varchar(50) = NULL,
	-- promocode
	@promo  varchar(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	DECLARE @USERID INT;
	DECLARE @ACCOUNTID INT;
	DECLARE @MAINACCID INT;
	DECLARE @PAYMENTSYSTEMID INT;
	DECLARE @OPERID INT;
	declare @partnerId int
	
    -- check parameters
	IF @svcid IS NULL OR @USER IS NULL OR @promo IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
	
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @MAINACCID = accid, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END

    -- resolve account id
    IF @ERROR = 0
	BEGIN
		IF NOT @ACCOUNT IS NULL -- account specified
			BEGIN
				SELECT @ACCOUNTID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @ACCOUNT;
				IF @ACCOUNTID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END
		ELSE -- resolve account by service
			BEGIN
				declare @active bit
				SELECT @active = active FROM UserServices 
					WHERE userid = @USERID AND serviceid = @svcid
				IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
				BEGIN
					exec sp_int_autoSubscribe @svcid = @svcid, @userid = @userid, @partnerId = @partnerId, @error = @ERROR OUTPUT
				END

				IF (@ERROR = 0)
				BEGIN
					--SELECT @ACCOUNTID = @MAINACCID;
					SELECT @ACCOUNTID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@USERID;	
					IF @ACCOUNTID IS NULL
						SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
				END
			END
	END		 
    
    -- internal activation   
	IF @ERROR = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Try to activate promocode: userid , accid, code', @USERID, @ACCOUNTID, @PROMO
		EXEC dbo.sp_int_promoActivate @svcid, @USERID, @ACCOUNTID, @PROMO, @OPERID OUTPUT, @ERROR OUTPUT
	END
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	EXEC dbo.sp_log_promoActivation @svcid = @svcid, -- int
									@userid = @USERID, -- int
									@accid = @ACCOUNTID, -- int
									@user = @user, -- varchar(80)
									@account = @account, -- varchar(50)
									@promo = @PROMO, -- varchar(80)
									@state = @ERROR, -- int
									@error = @errlog OUTPUT -- int
	
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getPaymentSystemsSummary]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/26
-- Update 1:    2010/05/11
-- Description:	Retrieves payments systems summary

CREATE PROCEDURE [dbo].[sp_rpt_payments_getPaymentSystemsSummary]
	@spid INT,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
AS
BEGIN

	IF OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL
	BEGIN
		--SELECT NULL AS PaymentSystem, NULL AS TotalAmount, NULL AS TotalCount 
		RETURN;
	END	
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate);

	
	SELECT PS.name AS PaymentSystem, SUM(OP.amount) AS TotalAmount, COUNT(OP.amount) AS TotalCount 
		FROM dbo.Operations AS OP WITH(NOLOCK)
		INNER JOIN dbo.PaymentSystems AS PS WITH(NOLOCK) ON OP.systemid=PS.id
		INNER JOIN ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK) ON OP.userid = PU.userid
		INNER JOIN ##tmp_rptPaymentsSystems AS TPS 	WITH(NOLOCK) ON OP.systemid = TPS.systemid

	WHERE 
		type>=100 AND type<200 
		AND PU.periodid = 1
		AND PU.spid=@spid
		AND TPS.spid=@spid 
		AND OP.executedat BETWEEN @fromDate AND @toDate
	GROUP BY PS.ID, PS.name
	
	
	/*SELECT PS.name AS PaymentSystem, SUM(OP.amount) AS TotalAmount, COUNT(OP.amount) AS TotalCount 
	FROM dbo.Operations AS OP WITH(NOLOCK)
	INNER JOIN dbo.PaymentSystems AS PS WITH(NOLOCK) ON OP.systemid=PS.id
	WHERE 
		type>=100 AND type<200 
		AND OP.userid IN (SELECT userid FROM ##tmp_rptPaymentsUsers AS PU WITH(NOLOCK)WHERE PU.spid=@spid AND PU.periodid = 1)
		AND OP.systemid IN (SELECT systemid FROM ##tmp_rptPaymentsSystems AS TPS WITH(NOLOCK) WHERE TPS.spid=@spid)
		AND OP.executedat BETWEEN @fromDate AND @toDate
	GROUP BY PS.ID, PS.name*/
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getGroups]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Andrey V. Limorov
-- Create date: 2010/04/27
-- Update 1:    2010/05/05 (4 new parameters for transaction count and total amount)
-- Update 2:    2010/05/11 
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_payments_getGroups]
	-- session id
	@spid INT = NULL
AS
BEGIN
	
	IF	OBJECT_ID('tempdb..##tmp_rptPaymentsGroups') is NULL
	BEGIN
		RETURN SELECT NULL AS spid, NULL AS groupid, NULL AS start, NULL AS finish;
	END	
	
	SET FMTONLY OFF;
	SELECT * FROM ##tmp_rptPaymentsGroups WITH(NOLOCK) WHERE spid = @spid;

END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getStatisticsByGroupID]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/29
-- Description:	Group statistic

CREATE PROCEDURE [dbo].[sp_rpt_payments_getStatisticsByGroupID]
	-- session id
	@spid INT,
	-- group id
	@groupID INT,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL
	-- from total amount
	
	
AS
BEGIN
	IF OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL
	BEGIN
		SELECT	
			NULL AS StuffPercent, 
			NULL AS AmountMoneyPercent,
			NULL AS TransactionCountPercent; 	
		RETURN 0;
	END
	
	-- DECLARE VARIABLES
	
	DECLARE @groupPreviousStuffCount AS DECIMAL(15,2)
--	DECLARE @groupPreviousInCurrentStuffCount AS DECIMAL
--	DECLARE @groupPreviousStuffPercent AS DECIMAL
	
	
	DECLARE @groupStuffPercent AS DECIMAL(15,2)
	DECLARE @groupAmountMoneyPercent AS DECIMAL(15,2)
	DECLARE @groupTransactionCountPercent AS DECIMAL(15,2)
	
	DECLARE @totalStuffCount AS DECIMAL(15,2)
	DECLARE @totalAmountMoneyCount AS DECIMAL(15,2)
	DECLARE @totalTransactionCount AS DECIMAL(15,2)
	
	DECLARE @groupStuffCount AS DECIMAL(15,2)
	DECLARE @groupAmountMoneyCount AS DECIMAL(15,2)
	DECLARE @groupTransactionCount AS DECIMAL(15,2)
	
	-- CALCULATE
	
	SELECT @groupPreviousStuffCount = COUNT(*) FROM ##tmp_rptPaymentsUsers WITH(NOLOCK) 
		WHERE groupid=@groupID AND spid=@spid AND periodid=0
	--SELECT @groupPreviousInCurrentStuffCount = COUNT(*) FROM ##tmp_rptPaymentsUsers WHERE groupid=@groupID AND spid=@spid AND periodid=1

	SELECT @groupStuffCount=COUNT(*) 
		FROM ##tmp_rptPaymentsUsers WITH(NOLOCK) WHERE groupid=@groupID AND spid=@spid AND periodid=1
	SELECT @totalStuffCount=COUNT(*) 
		FROM ##tmp_rptPaymentsUsers WITH(NOLOCK) WHERE spid=@spid AND periodid=1
	
	
	SELECT @totalAmountMoneyCount=SUM(OP.amount),  @totalTransactionCount=COUNT(OP.amount) 
		FROM dbo.Operations AS OP WITH(NOLOCK)
	WHERE type>=100 AND type<200 
		AND OP.userid IN (SELECT userid FROM ##tmp_rptPaymentsUsers WITH(NOLOCK) WHERE spid=@spid AND periodid = 1)
		AND OP.systemid IN (SELECT systemid FROM ##tmp_rptPaymentsSystems WITH(NOLOCK) WHERE spid=@spid)
		AND OP.executedat BETWEEN @fromDate AND @toDate
		
	SELECT @groupAmountMoneyCount=SUM(OP.amount), @groupTransactionCount=COUNT(OP.amount) FROM dbo.Operations AS OP
	WHERE type>=100 AND type<200 
		AND OP.userid IN (SELECT userid FROM ##tmp_rptPaymentsUsers WITH(NOLOCK) WHERE spid=@spid AND groupid=@groupID AND periodid = 1)
		AND OP.systemid IN (SELECT systemid FROM ##tmp_rptPaymentsSystems WITH(NOLOCK) WHERE spid=@spid)
		AND OP.executedat BETWEEN @fromDate AND @toDate	

	
	-- CHECK WITH ZERO
	
	IF (@totalStuffCount=0)
		SET @groupStuffPercent=0;
	ELSE
	SET @groupStuffPercent=@groupStuffCount *100 /@totalStuffCount;
	
	IF (@totalAmountMoneyCount=0)
		SET @groupAmountMoneyPercent=0;
	ELSE
		SET @groupAmountMoneyPercent=@groupAmountMoneyCount*100/@totalAmountMoneyCount;
	
	IF (@totalTransactionCount=0)
		SET @groupTransactionCountPercent=0;
	ELSE
		SET @groupTransactionCountPercent=@groupTransactionCount*100/@totalTransactionCount;
	
--	IF (@groupPreviousStuffCount=0)
--		SET @groupPreviousStuffPercent=0;
--	ELSE
--		SET @groupPreviousStuffPercent=@groupPreviousInCurrentStuffCount*100/@groupPreviousStuffCount;
	
	-- SELECT RESULT
	
	SELECT	
			--@groupPreviousStuffPercent AS PreviousStuffPercent,
			@groupStuffPercent AS StuffPercent, 
			@groupAmountMoneyPercent AS AmountMoneyPercent,
			@groupTransactionCountPercent AS TransactionCountPercent; 
END
GO
/****** Object:  Table [dbo].[WriteOffReserve]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WriteOffReserve](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[svcId] [int] NOT NULL,
	[userId] [int] NOT NULL,
	[accountId] [int] NOT NULL,
	[amount] [int] NOT NULL,
	[finishTime] [datetime] NOT NULL,
	[reason] [nvarchar](max) NOT NULL,
	[cbt] [bit] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_getStuffPercentByGroupID]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/29
-- Description:	Retrieves the percent between previous user group count and current one

CREATE PROCEDURE [dbo].[sp_rpt_payments_getStuffPercentByGroupID]
	-- session id
	@spid INT,
	-- group id
	@groupID INT
	
AS
BEGIN
	IF OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL
	BEGIN
		SELECT NULL AS OldGroup, NULL  AS PercentStuff
		RETURN;
	END	

	DECLARE @groupCount AS DECIMAL
	-- calculate the number of users in this group
	SELECT @groupCount=COUNT(userid) 
		FROM ##tmp_rptPaymentsUsers WITH(NOLOCK) WHERE groupid=@groupID AND periodid=1 AND spid=@spid;

	IF @groupCount<>0
	BEGIN
	
		SELECT PUO.groupid AS OldGroup, COUNT(*)*100/@groupCount AS PercentStuff
		FROM  ##tmp_rptPaymentsUsers AS PUN
		INNER JOIN ##tmp_rptPaymentsUsers AS PUO ON PUN.userid = PUO.userid
		WHERE
			PUN.spid=@spid AND PUO.spid=@spid 
			AND PUN.periodid = 1 AND PUO.periodid = 0	
			AND PUN.groupid = @groupID
		GROUP BY PUO.groupid 
	END
END
GO
/****** Object:  Table [dbo].[WriteOffsPaymentSystem]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WriteOffsPaymentSystem](
	[operationId] [int] NULL,
	[paymentSystemId] [int] NULL,
	[amount] [decimal](15, 2) NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_testTemp]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_rpt_testTemp]
AS
BEGIN
	DECLARE @id INT;
	
	if OBJECT_ID('tempdb..#paymentsTmp') is NULL
	BEGIN
		PRINT 'aga';
		CREATE TABLE #paymentsTmp(id int, name varchar(80));
	END		

	SELECT @id = MAX(id) FROM #paymentsTmp;
	
	IF @id IS NULL
		SET @id = 0;
	ELSE
		SET @id = @id+1;		

	INSERT INTO #paymentsTmp (id, name)
		VALUES (@id ,'bb'); 
	
	SET FMTONLY OFF;	
	
	SELECT *, @@SPID AS PID FROM #paymentsTmp;		
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_reserveAmount]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_reserveAmount]
	@userName nvarchar(80),
    @svcid int,
	@amount decimal,
	@reason nvarchar(max),
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	SET NOCOUNT ON;
	
	DECLARE @USERID INT;
	DECLARE @ACCOUNTID INT;
	DECLARE @CBT BIT
	DECLARE @partnerId int
	DECLARE @reserveId int
	
    -- check parameters
	IF ( @userName IS NULL or @SVCID IS NULL or @amount IS NULL or @amount <= 0 or @reason IS NULL )
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @partnerId = partnerid FROM USERS WHERE [name] = @userName;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END
	-- resolve accountId
	IF @ERROR = 0
	BEGIN
		declare @active bit
		SELECT @active = active FROM UserServices 
			WHERE userid = @USERID AND serviceid = @svcid
		IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
		BEGIN
			exec sp_int_autoSubscribe @svcid = @svcid, @userid = @USERID, @partnerId = @partnerId, @error = @ERROR OUTPUT
		END
	END

	IF @ERROR = 0
	BEGIN
		SELECT @ACCOUNTID = opId, @CBT = cbtMode FROM dbo.vw_api_accountMap WHERE userid=@USERID AND serviceId=@svcid;
		IF @ACCOUNTID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
	END

	IF @ERROR = 0
	BEGIN
		-- delete obsolete reserves
		BEGIN TRAN DeleteObsolete
		delete from WriteOffReserve where accountId = @ACCOUNTID and cbt = @CBT and finishTime <= GETDATE();
		COMMIT TRAN DeleteObsolete

		-- see, if there is more reserves
		declare @allreadyReserved decimal
		select @allreadyReserved = sum(amount) from WriteOffReserve where accountId = @ACCOUNTID and cbt = @CBT
	END

	--check amount smaller than balance
	IF @ERROR = 0
	BEGIN
		declare @cbtpsid INT;
		declare @currBalance decimal
		SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();

		SELECT @currBalance = SUM(amount) FROM dbo.SubAccounts 
			WHERE accid=@ACCOUNTID AND ((@CBT=1 AND systemId=@cbtpsid) OR (@CBT=0 AND systemId<>@cbtpsid))

		if  ( @amount + isnull(@allreadyReserved, 0) > @currBalance )
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
	END

	IF @error <> 0
		RETURN -1;
	
	insert WriteOffReserve (svcId, userId, accountId, amount, finishTime, reason, cbt)
		values (@svcid, @USERID, @ACCOUNTID, @amount, DATEADD(minute , 2, GETDATE()), @reason, @CBT )
	
	select @reserveId = @@identity
--	SELECT SUM(amount) AS AMOUNT FROM dbo.VW_UserBalance WHERE	id = @userid AND systemid <>@cbtpsid

	-- log request ============================================================================	
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':reserveId=' + cast(@reserveId as nvarchar(11)) +
		':@account='  + CASE WHEN @ACCOUNTID IS NULL THEN 'null' ELSE cast(@ACCOUNTID as varchar(50)) END +
		':cbt=' + cast(@CBT as varchar(1)) +
		':@reason='  + cast(@reason as VARCHAR(2000));
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 516, @serviceid=@svcid, @userid = @userid, @operationid = null, 
		@amount = @amount, @parameters = @content, @result = @error, @error = @errlog OUTPUT
	-- end log request ============================================================================	
	
	SELECT @reserveId as reserveId
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [users].[get_PassiveUsers]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Motulskaya Alexandra>
-- Create date: <2010-09-15>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [users].[get_PassiveUsers]
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	DECLARE user_cursor CURSOR STATIC FOR
		select u.id, u.name, p.createdat, p.email from BillingTest.dbo.Users u, BillingTest.dbo.Profiles p where u.id=p.userid
		and p.createdat between dateadd(day,(-31),GETDATE()) and GETDATE()
		--and p.createdat between dateadd(day,(-),'2010-08-30 00:00:00') and '2010-08-30 00:00:00'

	DECLARE @id nvarchar(80)
	DECLARE @name nvarchar(80)
	DECLARE @createdat datetime
	DECLARE @email varchar(80)

	SET NOCOUNT ON

	CREATE TABLE #logins (userid int NOT NULL)

	insert into #logins
		select distinct userid from BillingTest.dbo.Protocols p
		where p.serviceid in (select s.id from BillingTest.dbo.Services s where s.cbtMode=0)
		and p.typeid=501 and p.result = 0 and p.occurredat between dateadd(day,(-31),GETDATE()) and GETDATE()
		--and p.typeid=501 and p.result = 0 and p.occurredat between dateadd(day,(-3),'2010-08-30 00:00:00') and '2010-08-30 00:00:00'
	
	delete from BillingTest.users.Passive

	OPEN user_cursor

	FETCH NEXT FROM user_cursor INTO @id, @name, @createdat, @email

	WHILE @@FETCH_STATUS = 0
	BEGIN
		if not exists(select * from #logins where userid=@id) 
		BEGIN
			print @name + ' ' + cast(@createdat as varchar) + ' ' +@email
			insert into BillingTest.users.Passive([name], createdat, email) values (@name,@createdat,@email)
		END
		FETCH NEXT FROM user_cursor INTO @id, @name, @createdat, @email
	END

	CLOSE user_cursor
	DEALLOCATE user_cursor
	drop table #logins

END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_setUserPassword]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/06/09
-- Description:	Updates user password
-- =============================================
CREATE PROCEDURE [dbo].[sp_api_setUserPassword]
	-- user name, cannot be null
	@user varchar(80),
	-- password
	@password varbinary(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
SET NOCOUNT ON;
	
	SELECT @error = 0;
	DECLARE @USERID INT;
	
	-- check parameters	
	IF @USER IS NULL OR @password IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END

    IF @ERROR = 0
    BEGIN
		UPDATE dbo.Users SET password = @password WHERE id = @USERID

		IF @@ROWCOUNT = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Cannot find user profile', @userid, @@ERROR;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END
	END
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;

	EXEC dbo.sp_log_setUserPassword @userid = @USERID, -- int
									@user = @USER, -- varchar(80)
									@password = @password, -- varbinary(80)
									@state = @ERROR, -- int
									@error = @errlog OUTPUT -- int
	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================

	if @ERROR = 0
		RETURN 0;

	RETURN -1;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_setUserProfile]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/15
-- Description:	Updates extended user info

CREATE PROCEDURE [dbo].[sp_api_setUserProfile]
	-- service id
	@svcid INT,
	-- user name, cannot be null
	@user varchar(80),
	-- display name of user
	@displayName varchar(200),
	-- email address
	@email VARCHAR(80),
	-- agreement 
	@agreement bit,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	
	SELECT @error = 0;
	DECLARE @USERID INT;
	
	-- check parameters	
	IF @USER IS NULL OR @email IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    DECLARE @PARTNERID INT;
    SELECT @PARTNERID = partnerid FROM dbo.Users WHERE id = @USERID;
    
    -- check existing of user with the same e-mail
	IF @ERROR = 0
	BEGIN	
		IF	EXISTS (SELECT USERID FROM dbo.Profiles 
					WHERE email = @email AND 
					ISNULL(@PARTNERID,0) = ISNULL((SELECT partnerid FROM dbo.Users WHERE id = USERID),0))
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_EMAIL_EXISTS');
	END

    IF @ERROR = 0
    BEGIN
		UPDATE PROFILES SET AGREEMENT = @agreement, EMAIL = @email, DISPLAYNAME=@displayName
			WHERE USERID=@USERID

		IF @@ROWCOUNT = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Cannot find user profile', @userid, @@ERROR;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END
	END
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_setUserProfile  @svcid = @svcid,
									@userid = @USERID, -- int
									@user = @USER, -- varchar(80)
									@displayName = @displayName, -- varchar(200)
									@email = @email, -- varchar(80)
									@agreement = @agreement, -- bit
									@state = @ERROR, -- int
									@error = @errlog OUTPUT -- int
	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================

	if @ERROR = 0
		RETURN 0;

	RETURN -1;
END
GO
/****** Object:  Table [dbo].[Currencies]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Currencies](
	[id] [int] NOT NULL,
	[name] [varchar](20) NOT NULL,
	[rate] [decimal](15, 2) NOT NULL,
 CONSTRAINT [XPKCurrencies] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Employees]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Employees](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](80) NOT NULL,
	[password] [varbinary](80) NOT NULL,
	[groupid] [int] NOT NULL,
 CONSTRAINT [XPKEmployees] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Operations]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Operations](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[amount] [decimal](15, 2) NOT NULL,
	[userid] [int] NULL,
	[executedat] [datetime] NOT NULL,
	[type] [int] NOT NULL,
	[srcaccid] [int] NULL,
	[destaccid] [int] NULL,
	[reason] [varchar](max) NULL,
	[empid] [int] NULL,
	[systemid] [int] NULL,
	[serviceid] [int] NULL,
 CONSTRAINT [XPKOperations] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Users]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Users](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](80) NOT NULL,
	[password] [varbinary](80) NOT NULL,
	[accid] [int] NULL,
	[partnerid] [int] NULL,
	[finalBan] [bit] NULL,
	[tempBan] [datetime] NULL,
 CONSTRAINT [XPKUsers] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ReferalCodes]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ReferalCodes](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[partnerid] [int] NOT NULL,
	[mask] [varchar](80) NOT NULL,
 CONSTRAINT [XPKReferalCodes] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ProtocolPaymentSystems]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ProtocolPaymentSystems](
	[systemid] [int] NOT NULL,
 CONSTRAINT [XPKProtocolPaymentSystems] PRIMARY KEY NONCLUSTERED 
(
	[systemid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[SubAccounts]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[SubAccounts](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[systemid] [int] NULL,
	[amount] [decimal](15, 2) NOT NULL,
	[accid] [int] NULL,
 CONSTRAINT [XPKSubAccounts] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LegacyServices]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LegacyServices](
	[id] [varchar](80) NOT NULL,
	[serviceid] [int] NOT NULL,
	[ip] [varchar](20) NOT NULL,
	[password] [varchar](80) NOT NULL,
 CONSTRAINT [XPKLegacyServices] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ProtocolServices]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ProtocolServices](
	[serviceid] [int] NOT NULL,
 CONSTRAINT [XPKProtocolServices] PRIMARY KEY NONCLUSTERED 
(
	[serviceid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Profiles]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Profiles](
	[createdat] [datetime] NOT NULL,
	[referalCode] [varchar](80) NULL,
	[userid] [int] NOT NULL,
	[agreement] [bit] NOT NULL,
	[email] [varchar](80) NULL,
	[templateid] [int] NULL,
	[displayName] [varchar](200) NULL,
 CONSTRAINT [XPKProfiles] PRIMARY KEY NONCLUSTERED 
(
	[userid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UserServices]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserServices](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[userid] [int] NOT NULL,
	[serviceid] [int] NOT NULL,
	[accountid] [int] NOT NULL,
	[active] [bit] NOT NULL,
	[ban] [bit] NOT NULL,
	[banReason] [text] NULL,
	[properties] [xml] NULL,
	[password] [varbinary](80) NULL,
 CONSTRAINT [XPKUserServices] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Transactions]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Transactions](
	[operationid] [int] NOT NULL,
	[subaccid] [int] NOT NULL,
	[amount] [decimal](15, 2) NOT NULL,
	[id] [int] IDENTITY(1,1) NOT NULL,
 CONSTRAINT [XPKTransactions] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Promocodes]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Promocodes](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[code] [varchar](80) NOT NULL,
	[generatedat] [datetime] NOT NULL,
	[operationid] [int] NULL,
	[amount] [decimal](15, 2) NOT NULL,
 CONSTRAINT [XPKPromocodes] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Accounts]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Accounts](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [varchar](50) NOT NULL,
	[userid] [int] NOT NULL,
 CONSTRAINT [XPKAccounts] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Sessions]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Sessions](
	[usrservid] [int] NULL,
	[logonat] [datetime] NOT NULL,
	[id] [varchar](80) NOT NULL,
	[logoffat] [datetime] NULL,
 CONSTRAINT [XPKSessions] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Services]    Script Date: 09/08/2013 16:06:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Services](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [nvarchar](80) NOT NULL,
	[description] [text] NULL,
	[cbtMode] [bit] NOT NULL CONSTRAINT [DF_Services_cbtMode]  DEFAULT ((0)),
	[password] [varbinary](80) NOT NULL,
	[currencyid] [int] NULL,
	[independent] [bit] NOT NULL,
	[trusted] [bit] NOT NULL,
 CONSTRAINT [XPKServices] PRIMARY KEY NONCLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_saveTemplate]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/03/10
-- Description:	create / update template
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_saveTemplate] 
	-- parameters for the stored procedure
	-- id of template or null for new
	@id				INT = NULL,
	-- name of template
	@name			nvarchar(80), 
	-- description
	@description	text, 
	-- apply mask
	@mask			varchar(80), 
	-- template parameters
	@parameters		xml,
	-- employer ID
	@empid			INT,
	-- error code
	@error			int OUTPUT

AS
BEGIN
	SELECT @error = 0;
	DECLARE @resId INT;
	DECLARE @priority INT;

    IF @name IS NULL OR @parameters IS NULL OR @empid IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END

	-- check administrator
	IF @ERROR = 0
	BEGIN
		DECLARE @grpid INT;
		
		SELECT @grpid = groupid FROM dbo.Employees WHERE id = @empid;
		IF @grpid IS NULL
		BEGIN
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			SET @empid = NULL;
		END			
        ELSE IF @grpid<>1
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
	END	
	
	IF @ERROR = 0
	BEGIN
		BEGIN TRANSACTION T_saveTemplate
		IF @ID IS NULL
			BEGIN
				  SELECT @priority = MAX(priority)+1 from DBO.TEMPLATES;
				  IF @priority IS NULL
					   SELECT @priority = 1;
				
				  INSERT INTO DBO.TEMPLATES (name, description, mask, priority, parameters)
				  VALUES (@name, @description, @mask, @priority, @parameters)
		  		
				  IF @@ERROR<>0
					  SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
				  ELSE
					  SET @resId = SCOPE_IDENTITY();

			END
		ELSE
			BEGIN
			  UPDATE DBO.TEMPLATES
				SET name=@name, description=@description, mask=@mask, parameters=@parameters
				WHERE id=@id

			  IF( @@ROWCOUNT = 0 )
				  SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			  ELSE
				  SET @resId = @id;
			END

		IF  @ERROR = 0
			COMMIT TRANSACTION T_saveTemplate
		ELSE
			ROLLBACK TRANSACTION T_saveTemplate			
	END
	
	IF @error <>0 
		RETURN -1;

	SELECT @resId as ID;
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_adminWriteOff]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Does admin writes-off money
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_adminWriteOff]
	-- id of administrator
	@empid INT,
	-- password of administrator
	@password VARBINARY(80),
	-- user id
	@userid INT,
	-- account id
	@accid INT,
	-- payment system id
	@systemid INT = NULL,
	--ammount to write off
	@amount DECIMAL(15,2),	
	-- reason of operation
	@reason text,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	DECLARE @operid INT;
	DECLARE @opaccid INT;
	
	-- check parameters
	IF  @empid IS NULL OR @password IS NULL OR @userid IS NULL OR @amount IS NULL OR @amount<=0 OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
	
	-- check administrator
	IF @ERROR = 0
	BEGIN
		DECLARE @emppass VARBINARY(80);
		DECLARE @grpid INT;
		
		SELECT @grpid = groupid, @emppass = password FROM dbo.Employees WHERE id = @empid;
		IF @grpid IS NULL
		BEGIN
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			SET @empid = NULL;
		END			
        ELSE IF @emppass IS NULL OR @emppass <> @password
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_PASSWORD');
        ELSE IF @grpid<>1
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
	END	
	
	-- check payment system
    
	IF @ERROR = 0 AND NOT @systemid IS NULL
	BEGIN
		IF NOT EXISTS (SELECT * FROM dbo.PaymentSystems WHERE id = @systemid)
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNKNOWN_PAYMENT_SYSTEM');
	END	
	
	-- check user
	IF @ERROR = 0 AND NOT EXISTS (SELECT * FROM dbo.Users WHERE id = @userid)
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		EXEC dbo.sp_int_trace 'No user',@userid
	END		
	
	-- resolve account id
	IF @ERROR = 0
	BEGIN
		IF @accid IS NULL
			SELECT @opaccid = accid FROM dbo.Users WHERE id = @userid;
		ELSE			
			SELECT @opaccid = OPID FROM dbo.vw_api_accountMap WHERE accId = @accid;
		 IF @opaccid IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');	
	END		
	
	-- internal admin writeoff
	IF @ERROR = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Try to do admin write-off', @empid, @USERID, @accid, @AMOUNT, @systemid
		
		EXEC dbo.sp_int_adminWriteOff	@EMPID = @empid, -- int
										@USERID = @userid, -- int
										@ACCID = @opaccid, -- int
										@AMOUNT = @amount, -- decimal
										@SYSTEMID = @systemid, -- int
										@REASON = @reason, -- text
										@OPERID = @operid OUTPUT, -- int
										@error = @ERROR OUTPUT; -- int
	END

	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_adminWriteOff	@empid =	@empid, -- int
									@userid = @userid, -- int
									@systemid = @systemid, -- int
									@amount = @amount, -- decimal
									@operationid = @operid, -- int
									@accid = @opaccid, -- int
									@reason = @reason, -- text
									@state = @ERROR, -- int
									@error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================

	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_adminWriteOffHistory]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/04/14
-- Description:	Retrieves gma writeoff history

CREATE PROCEDURE [dbo].[sp_gui_adminWriteOffHistory]
	-- user name
	@userID INT,
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- from amount
	@fromAmount DECIMAL,
	-- to amount
	@toAmount DECIMAL,

	@gmaLogin NVARCHAR(80),
	-- payment system
	@reason TEXT,
	-- error code
	@error int OUTPUT
AS
BEGIN

	SELECT @ERROR = 0;
	
	DECLARE @count INT;
	
	-- check parameters
    IF @UserID IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END	
	
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @count=COUNT(*) FROM Users WHERE id=@userID
		IF @count=0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END

	IF @ERROR <> 0
		RETURN -1;
	
	SELECT OP.amount, OP.executedat, OP.reason, EM.name AS gmaLogin, OP.userid 
		FROM DBO.OPERATIONS AS OP,dbo.Employees AS EM
		WHERE  OP.type=202 AND OP.empid = EM.id
		AND OP.executedat BETWEEN @fromDate AND @toDate
		AND OP.amount BETWEEN @fromAmount AND @toAmount
		AND EM.name LIKE @gmaLogin
		AND OP.reason LIKE @reason
	ORDER BY OP.executedat ASC

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_AuthorizeAdministrator]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_AuthorizeAdministrator] 
(
	@username nvarchar(80),
	@password varbinary(80)
)	
AS
BEGIN
	SELECT groupid, id FROM dbo.Employees
		WHERE [name]=@username AND password=@password
		
	IF @@ROWCOUNT=1		
		RETURN 0;
	RETURN -1;		
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_generatePromocodes]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/15
-- Description:	Retrieves extended user info

CREATE PROCEDURE [dbo].[sp_gui_generatePromocodes]
	-- employer id
	@empid INT,
	-- count of promocodes
	@count INT,
	-- amount of every promo
	@amount DECIMAL(15,2),
	-- reason
	@reason varchar(max),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @error = 0;	
	DECLARE @OPERID INT;
	-- check parameters	
	IF @empid IS NULL OR @count IS NULL OR @amount IS NULL OR @count<=0 OR @amount <=0 
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    IF @ERROR = 0
		CREATE TABLE #TEMP_PROMO(code VARCHAR(80) COLLATE Cyrillic_General_CI_AS);
    
    -- resolve employer
    IF @ERROR = 0
    BEGIN
		DECLARE @groupid INT;
        SELECT @groupid = groupid FROM dbo.Employees WHERE id = @empid;
        
        IF @groupid IS NULL
        BEGIN
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
			SET @empid = NULL; 
		END            
        ELSE IF @groupid <> 1
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
    END

	-- get profiles info
    IF @ERROR = 0
    BEGIN
		DECLARE @fullamount DECIMAL(15,2);
		SET @fullamount = @amount * @count;
		
		BEGIN TRANSACTION CREATE_PROMO
		
        
		IF @ERROR = 0
		BEGIN
	    	EXEC dbo.sp_int_trace 'Try to create new gen promo operation', @empid, @fullamount, @count, @amount
			-- INSERT  NEW OPERATION ===========================
			INSERT INTO DBO.Operations
			        ( amount, executedat, type, reason, empid )
			VALUES  ( @fullamount, GETDATE(), 401, @reason, @empid);
			
			IF @@ERROR <> 0
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			ELSE
				SELECT @OPERID = SCOPE_IDENTITY();
		END
		
		IF @ERROR = 0
		BEGIN
			DECLARE @i INT; SET @i = 0;
			DECLARE @PID VARCHAR(100);
			WHILE( @i < @count AND @error = 0 )
			BEGIN
				EXEC dbo.sp_int_generate_rnd_string @digits = 16, @devider = '-', @groups = 4, @random = @PID OUTPUT;
				INSERT INTO #TEMP_PROMO  (code)
					VALUES(@PID);
				INSERT INTO dbo.Promocodes
				        ( code, generatedat, operationid, amount )
				VALUES  ( @PID, GETDATE(), NULL, @amount );
				IF @@ERROR <> 0
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
				ELSE
				
					SET @i = @i + 1;					
			END
		END
		
		IF @error =0
			COMMIT TRANSACTION CREATE_PROMO;
		ELSE
			ROLLBACK TRANSACTION CREATE_PROMO;	
			
		
	END


	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_generatePromocodes @empid = @empid, -- int
	    @fullamount = @fullamount, -- decimal
	    @operationid = @OPERID, -- int
	    @amount = @amount, -- decimal
	    @count = @count, -- int
	    @reason = @reason, -- varchar(80)
	    @state = @ERROR, -- int
	    @error = @errlog OUTPUT -- int
	    
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================

	SET NOCOUNT OFF;
	
	if @ERROR = 0
	BEGIN	
		SELECT  dbo.Promocodes.code,  dbo.Promocodes.amount,  dbo.Promocodes.generatedat
				FROM dbo.Promocodes, #TEMP_PROMO WHERE  #TEMP_PROMO.code =  dbo.Promocodes.code;
		RETURN 0;				
	END				

	RETURN -1;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_deleteTemplate]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/03/10
-- Description:	deleting template
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_deleteTemplate] 
	-- parameters for the stored procedure
	@id			int,
	@admid		int,
	@error int OUTPUT

AS
BEGIN
	SET @error = 0;
	
	DECLARE @templateId int

	if @id is NULL OR @admid IS NULL
	begin
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	end
	
	-- check administrator
	IF @ERROR = 0
	BEGIN
		DECLARE @grpid INT;
		
		SELECT @grpid = groupid FROM dbo.Employees WHERE id = @admid;
		IF @grpid IS NULL
		BEGIN
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			SET @admid = NULL;
		END			
        ELSE IF @grpid<>1
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
	END	
		
	IF @ERROR = 0
	BEGIN
		DELETE FROM DBO.TEMPLATES WHERE ID = @id

		IF @@ROWCOUNT = 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	END		
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1

END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getGMTransactions]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/05/03
-- Description:	Retrieves gm transactions
-- =============================================
CREATE PROCEDURE [dbo].[sp_rpt_getGMTransactions] 
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- user name mask
	@userName VARCHAR(200),
	-- from amount
	@fromAmount INT,
	-- to amount
	@toAmount INT,
	-- gma login
	@gmLogin VARCHAR(200),
	-- reason
	@comment VARCHAR(200)
	
AS
BEGIN

	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF @fDate IS NULL
		SELECT @fDate = CONVERT(DATETIME, '2000/01/01 00:00');
	
	IF @fDate IS NULL
		SELECT @tDate = CONVERT(DATETIME, '2100/01/30 00:00');	

-- create result request	
	SELECT dbo.Users.name AS UserName,
		executedat AS Date,
		amount AS Amount,
		dbo.Employees.name AS LoginGM,
		reason AS Reason
	FROM dbo.Operations, dbo.Users, dbo.Employees 
	WHERE type = '202' AND
		userid = dbo.Users.id AND
		executedat BETWEEN @fDate AND @tDate AND
		empid = dbo.Employees.id AND
		dbo.Users.name LIKE @userName AND
		amount BETWEEN @fromAmount AND @toAmount AND
		dbo.Employees.name LIKE @gmLogin AND
		reason LIKE @comment
	ORDER BY dbo.Users.name, executedat
	
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_get_error_code]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	Does translation of error messages to codes
-- =============================================
CREATE FUNCTION [dbo].[sf_int_get_error_code] (	@val varchar(80))

RETURNS varchar(4000)
AS
BEGIN
	DECLARE @ResultVar int;
	SELECT @ResultVar = code from ErrorCodes where name = @val; 
	IF @ResultVar IS NULL
	BEGIN
		SELECT @ResultVar = -1
	END
	
	RETURN @ResultVar
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_send_admin_fraud_mail]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Does sending of fraud notification message to administrator

CREATE PROCEDURE [dbo].[sp_int_send_admin_fraud_mail]
	-- 	service id, cannot be null
	@svcid INT,
	-- user id, cannot be null
	@userid INT,
	-- fraud parameter	
	@parameter VARCHAR(80),
	-- fraud level	
	@level INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @error = 0;
		
	DECLARE @descr VARCHAR(200);

	-- check parameters	
	IF @svcid IS NULL OR @userid IS NULL OR @parameter IS NULL OR @level IS NULL OR NOT @level BETWEEN 1 AND 2
	BEGIN
		EXEC dbo.sp_int_trace 'Invalid parameters for sp_int_send_admin_fraud_mail', @svcid, @svcid, @userid, @parameter
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
   
    -- resolve user
    IF @ERROR = 0
    BEGIN
		SELECT @descr = description FROM dbo.FraudSettings WHERE code = @parameter;
        IF @descr IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
    END

    
	IF @ERROR = 0
    BEGIN
		DECLARE @mailType INT;
		IF @level = 1
			SET @mailType = 201;
		ELSE			
			SET @mailType = 202;
		EXEC dbo.sp_int_send_mail @type = @mailType, -- int
			    @svcid = @svcid, -- int
			    @userid = @userid, -- int
			    @adminMail = 1, -- varchar(100)
			    @param1 = @descr, -- nvarchar(200)
			    @error = @error OUTPUT -- int
			    
    END

	if @ERROR<>0
	BEGIN
		EXEC dbo.sp_int_trace 'Unable to send fraud notify message with', @svcid, @userid, @descr, @ERROR
		RETURN -1;
	END		

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_checkFraudValue]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/24
-- Description:	Does checking of fraud settings
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_checkFraudValue]
	@code VARCHAR(50),
	@value	DECIMAL(15,2),
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @value IS NULL or @switch=0
    	RETURN 0;
    		
	DECLARE @yval DECIMAL(15,2), @rval DECIMAL(15,2)
	--EXEC dbo.sp_int_trace 'Try to check value', @code, @value
    IF @code IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
	
	IF @error=0
	BEGIN
		SELECT @yval =yellow, @rval = red FROM dbo.FraudSettings WHERE code = @code;
		IF @@ROWCOUNT<>1
		BEGIN
			EXEC dbo.sp_int_trace 'Unable to find fraud settings', @code
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END
	END
	
	IF @error=0 
	BEGIN
		IF @value>=@rval
		BEGIN
			EXEC dbo.sp_int_trace 'Red level detected',@code, @value, @yval, @rval  
			-- send description to client
			DECLARE @descr AS VARCHAR(200);
			SELECT @descr = description FROM dbo.FraudSettings WHERE code = @code;
			SET @descr = 'Red level detected :' + @descr; 
			-- uncoment it to get readable error description
			--RAISERROR (@descr, 16, 1 );
			RETURN 2;
		END			
		
		IF NOT @yval IS NULL AND @value>=@yval
		BEGIN
			EXEC dbo.sp_int_trace 'Yellow level detected',@code, @value, @yval, @rval 
			RETURN 1;
		END	
		EXEC dbo.sp_int_trace 'No fraud detected',@code, @value, @yval, @rval 		
		RETURN 0;
	END
	
	RETURN -1;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_legacy_getServicePassword]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	does searching of service by name and checks CRC

CREATE PROCEDURE [dbo].[sp_legacy_getServicePassword]
	-- service legacy id
	@legacyId varchar(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	-- check parameters
    IF @legacyId IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END

	-- RETRIEVE DATA
	SELECT SV.ID, SV.NAME, LS.PASSWORD FROM dbo.LegacyServices AS LS,dbo.Services AS SV 
		WHERE LS.id = @legacyId AND SV.id = LS.serviceid;
	
	if @@ROWCOUNT = 0
	begin
		select @error = dbo.sf_int_get_error_code('E_INVALID_SERVICE');
		return -1;
	end
	RETURN 0;	
END
GO
/****** Object:  View [dbo].[vw_migr_WriteOffs]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create view [dbo].[vw_migr_WriteOffs]
as
SELECT     zl.username, cast((zl.money_before - zl.money_after) as decimal(15,2)) as amount, zl.pubdate, zl.clientid as oldSvcID, zl.serviceid as oldReason, us.id as newUserId, us.accid as comAccId, ls.serviceid AS newSvcId
FROM         dbo.zzgold_logs AS zl LEFT OUTER JOIN
                      dbo.Users AS us ON zl.username = us.name LEFT OUTER JOIN
                      dbo.LegacyServices AS ls ON ls.id = zl.clientid
WHERE     (zl.money_before > zl.money_after and zl.clientid <> 0)
GO
/****** Object:  StoredProcedure [dbo].[sp_int_send_mail]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- does sending of message
CREATE PROCEDURE [dbo].[sp_int_send_mail]
	@type INT,
	@svcid INT,
	@userid INT,

	-- is mail to admin or not
	@adminMail bit,
	@param1 NVARCHAR(200) = NULL,
	@param2 NVARCHAR(200) = NULL,
	
	-- error code, if any
	@error INT OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @error = 0;
	
	DECLARE @userName VARCHAR(80);
	DECLARE @serviceName VARCHAR(80);
	DECLARE @userDisplay NVARCHAR(200);
	DECLARE @email VARCHAR(80);
	
	DECLARE @subject NVARCHAR(200);
	DECLARE @body NVARCHAR(MAX);
	
	
	IF @error=0
	BEGIN
		SELECT @userName = NAME, @userDisplay = displayName, @email = email FROM dbo.Users, dbo.Profiles
			WHERE dbo.Users.id = @userid AND dbo.Users.id =  dbo.Profiles.userid
		IF @userName IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		ELSE IF @userDisplay IS NULL	
			SELECT 	@userDisplay = @userName;	
	
	END
	
	IF @error = 0 AND @adminMail = 1
		SET @email = NULL;
	
	IF @error=0
	BEGIN
		SELECT @serviceName = name FROM dbo.Services
			WHERE id = @svcid
		IF @serviceName IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');			
	
	END
		
	IF @error = 0
	BEGIN
		SELECT @subject = subject, @body = body FROM dbo.MailTemplates WHERE id = @type;
		IF @subject IS NULL OR @body IS NULL
		BEGIN
			EXEC dbo.sp_int_trace 'unable to find mail template with type', @type;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');			
		END			
	END
	
	
	IF @error = 0
	BEGIN
		SET @subject = REPLACE(@subject,'%USERNAME%',@userName);
		SET @subject = REPLACE(@subject,'%USERDISPLAYNAME%',@userDisplay);
		SET @subject = REPLACE(@subject,'%SERVICENAME%',@serviceName);
		IF (NOT @param1 IS NULL)
			SET @subject = REPLACE(@subject,'%PARAM1%',@param1);
		IF (NOT @param2 IS NULL)
			SET @subject = REPLACE(@subject,'%PARAM2%',@param2);			
		
		
		SET @body = REPLACE(@body,'%USERNAME%',@userName);
		SET @body = REPLACE(@body,'%USERDISPLAYNAME%',@userDisplay);
		SET @body = REPLACE(@body,'%SERVICENAME%',@serviceName);
		IF (NOT @param1 IS NULL)
			SET @body = REPLACE(@body,'%PARAM1%',@param1);
		IF (NOT @param2 IS NULL)
			SET @body = REPLACE(@body,'%PARAM2%',@param2);			
		
		EXEC dbo.sp_int_send_raw_mail @to = @email, -- varchar(100)
		    @subject = @subject, -- varchar(100)
		    @body = @body, -- varchar(4000)
		    @error = @error OUTPUT -- int
		
	END		

	IF @error = 0
		RETURN 0;

	RETURN -1;											
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_resolve_partner_program]    Script Date: 09/08/2013 16:06:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/03
-- Description:	Does resolving of partner program
-- =============================================
CREATE FUNCTION [dbo].[sf_int_resolve_partner_program] (	@REFERAL VARCHAR(4000))
RETURNS INT
AS
BEGIN
	DECLARE @RESULTVAR INT;
	SET @RESULTVAR = NULL;

	IF @REFERAL IS NULL
		RETURN @RESULTVAR;

	SELECT TOP 1 @RESULTVAR=PP.ID FROM DBO.PARTNERPROGRAMS AS PP, DBO.REFERALCODES AS RC
		WHERE PP.ID = RC.PARTNERID AND @REFERAL LIKE RC.MASK
	RETURN @RESULTVAR

END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getUserProfile]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getUserProfile]
	-- user name, cannot be null
	@user varchar(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @USERID INT;
	DECLARE @finalBan bit
	DECLARE @tempBan datetime
	declare @ban nvarchar(32)

	SELECT @error = 0;
	select @ban = null
	-- check parameters	
	IF @USER IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END 

	declare @userName nvarchar(80)
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID, @userName = [name], @finalBan = finalBan, @tempBan = tempBan FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END

	if @ERROR = 0
	BEGIN
		if (@finalBan = 1)
			set @ban = 'totalBan'
		else
			if (@tempBan is not null)
				if (@tempBan > getdate())
					set @ban = convert(nvarchar(32), @tempBan, 120)
	END
	-- get profiles info
    IF @ERROR = 0
    BEGIN
		SELECT @USERID as USERID,
				CREATEDAT, 
				REFERALCODE, 
				EMAIL, 
				isnull( DISPLAYNAME, @userName) as DISPLAYNAME, 
				(SELECT DBO.PARTNERPROGRAMS.NAME FROM DBO.PARTNERPROGRAMS, DBO.USERS
					WHERE DBO.PARTNERPROGRAMS.ID=PARTNERID AND DBO.USERS.ID=@USERID) AS PARTNER, 
				AGREEMENT,
				@ban as BAN
			FROM DBO.PROFILES
			WHERE DBO.PROFILES.USERID=@USERID 

		IF @@ROWCOUNT = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Cannot find user profile', @userid, @@ERROR;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END
	END

	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_byIdGetUserProfile]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_byIdGetUserProfile]
	-- user name, cannot be null
	@userid int,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;

	SELECT @error = 0;

	-- check parameters	
	IF @userid IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END
	DECLARE @userName nvarchar(80)
	DECLARE @finalBan bit
	DECLARE @tempBan datetime
	declare @ban nvarchar(32) 
	
	-- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @userName = [name], @finalBan = finalBan, @tempBan = tempBan FROM USERS WHERE Users.id = @userid
        IF @userName IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
	
	--generate ban field if necessary
	if @ERROR = 0
	BEGIN
		if (@finalBan = 1)
			set @ban = 'totalBan'
		else
			if (@tempBan is not null)
				if (@tempBan > getdate())
					set @ban = convert(nvarchar(32), @tempBan, 120)
	END

	-- get profiles info
	IF @ERROR = 0
    BEGIN
		SELECT @userName as [name],
				CREATEDAT, 
				REFERALCODE, 
				EMAIL, 
				isnull( DISPLAYNAME, @userName) as DISPLAYNAME, 
				(SELECT DBO.PARTNERPROGRAMS.NAME FROM DBO.PARTNERPROGRAMS, DBO.USERS
					WHERE DBO.PARTNERPROGRAMS.ID=PARTNERID AND DBO.USERS.ID=@USERID) AS PARTNER, 
				AGREEMENT,
				@ban as BAN
			FROM DBO.PROFILES
			WHERE DBO.PROFILES.USERID=@userid 

		IF @@ROWCOUNT = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Cannot find user profile', @userid, @@ERROR;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END
	END

	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_findUserByEmail]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_findUserByEmail] 
	-- email to find user(s)
	@email varchar(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	-- check parameters	
	IF @email IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
	
	if not exists (select email from Profiles where email = @email)
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		RETURN -1;
	END
	
	select us.[name] as USERNAME, pp.[name] as PARTNERNAME from Profiles pr 
		inner join Users us on pr.userid = us.id
		left join PartnerPrograms pp on us.partnerid = pp.id
		where pr.email = @email;
	return 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_authorizeUser]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_authorizeUser]
	-- service id
	@svcid INT,
	-- user name
	@user varchar(80),
	-- password
	@password varbinary(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	declare @USERID INT;
	declare @PSWD VARBINARY(80);
	declare @SPCPSWD VARBINARY(80);
	declare @PARTNERID INT;
	declare @AUTHORIZATIONCLASS VARCHAR(80);
	declare @finalBan bit
	declare @tempBan datetime
	
	SELECT @error = 0;

	-- check parameters	
	IF @USER IS NULL OR @svcid IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END
	
	-- find user
	IF @error = 0
	BEGIN
		SELECT @USERID = US.ID, @PSWD = US.PASSWORD, @PARTNERID = US.PARTNERID, @finalBan = US.finalBan, @tempBan = US.tempBan, @AUTHORIZATIONCLASS =PP.AUTHORIZATIONCLASS
			FROM USERS AS US
			LEFT JOIN PARTNERPROGRAMS AS PP ON PP.ID = US.PARTNERID
			WHERE US.NAME = @USER
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID, @AUTHORIZATIONCLASS
	END			
	
	--check for ban on Zzima.com (service = sn)
	IF (@error = 0)
	BEGIN
		if (@svcid = 11) --HARDCODE FOR "SN"
		BEGIN
			if (@finalBan = 1)
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
			if (@tempBan is not null)
				if (getdate() <= @tempBan)
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
				else
					update Users set tempBan = null where id = @USERID
		END
	END
	
	--check subscription, and auto-subscription
	IF @error = 0
	BEGIN
		DECLARE @active bit;
		DECLARE @ban bit;
		SELECT @ban = ban, @active = active, @SPCPSWD = PASSWORD FROM UserServices 
			WHERE userid = @USERID AND serviceid = @svcid;
		IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
		BEGIN
			declare @template xml
			SELECT @template = PARAMETERS FROM DBO.TEMPLATES WHERE isnull(partnerId, 0) = isnull(@PARTNERID, 0)
			if ( @template.exist('/template/service[id=sql:variable("@svcid")]') = 1 )
			BEGIN
				declare @errorInSubscribe int
				select @errorInSubscribe = 0
				EXEC dbo.sp_int_subscribeUser	@USERID = @userid, -- int
												@SERVICEID = @svcid, -- int
												@password = NULL, -- varbinary(80)
												@error =  @errorInSubscribe OUTPUT -- int
				if (@errorInSubscribe <> 0)
					select @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END
			else
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		END
		else --if record exist check its activity and not banned 
		BEGIN
			IF @ban = 1	-- check for ban
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
			ELSE IF @active = 0 --check for activity
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
			ELSE IF NOT @SPCPSWD IS NULL
			BEGIN
				EXEC dbo.sp_int_trace 'Special password detected', @USERID, @PSWD, @SPCPSWD
				SELECT @PSWD = @SPCPSWD
			END
		END	
	END
-- check for subscription   ---old version
--	IF @error = 0
--	BEGIN
--		DECLARE @ban bit;
--		SELECT @ban = UserServices.ban, @SPCPSWD = PASSWORD FROM UserServices 
--			WHERE userid = @USERID AND serviceid = @svcid AND active=1;
--		
--		IF @ban IS NULL -- check for existing
--			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
--		ELSE IF @ban = 1	-- check for ban
--			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
--		ELSE IF NOT @SPCPSWD IS NULL
--		BEGIN
--			EXEC dbo.sp_int_trace 'Special password detected', @USERID, @PSWD, @SPCPSWD
--			SELECT @PSWD = @SPCPSWD
--		END			
--				
--	END
	
	-- check for fraud
	IF @error = 0
	BEGIN
		EXEC dbo.sp_int_pre_checkFraudLogin		@svcid = @svcid, -- int
												@userid = @USERID, -- int
												@error = @error OUTPUT -- int
	END
	

	-- compare passwords
	IF @error = 0 AND @AUTHORIZATIONCLASS IS NULL
	BEGIN
		IF	@PSWD <> @password 
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_PASSWORD');
	END

	-- check for fraud
	IF @error <> 0 AND NOT @userid IS NULL
	BEGIN
		EXEC dbo.sp_int_post_checkFraudLogin	@svcid = @svcid, -- int
												@userid = @userid, -- int
												@state = @error,
												@error = @error OUTPUT -- int
	END			

	SELECT @USERID AS id, 
		(CASE WHEN @AUTHORIZATIONCLASS IS NULL THEN 1 ELSE 0 END) AS authorized, 
		@PARTNERID AS partnerid, 
		@AUTHORIZATIONCLASS AS authorizationclass, 
		email AS email
	FROM dbo.Profiles 
	WHERE userid = @USERID
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	SELECT @svcid AS svcid, @USERID AS USERID, @user AS username, @password AS password, @error AS error, @errlog AS errlog;
	
	EXEC dbo.sp_log_authorizeUser  @svcid = @svcid, 
								   @userid = @USERID, 
								   @user=@user, 
								   @password = @password, 
								   @state = @error, 
								   @error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END	
	-- end log request ============================================================================
	
	IF @error <> 0
		RETURN -1
	
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getPaidUsers]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/26
-- Description:	Gets a table of paid users

CREATE PROCEDURE [dbo].[sp_rpt_getPaidUsers]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	SELECT  US.name AS Username, OP.executedat AS Date,
	OP.amount AS Amount, PS.name AS PaymentSystem
	FROM dbo.Operations AS OP
		INNER JOIN dbo.Users AS US ON OP.userid=US.id
		INNER JOIN dbo.PaymentSystems AS PS ON OP.systemid=PS.id
		WHERE OP.type>=100 AND OP.type<200 AND OP.systemid<>1 AND OP.systemid<>2
		AND executedat BETWEEN @fDate AND @tDate	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getPaymentsSummaryByPS]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/26
-- Description:	Retrieves count of game logins

CREATE PROCEDURE [dbo].[sp_rpt_getPaymentsSummaryByPS]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	SELECT PS.name AS PaymentSystem, 
	COUNT(OP.amount) AS Count, 
	SUM(OP.amount) AS Amount FROM dbo.Operations AS OP
	INNER JOIN dbo.PaymentSystems AS PS ON OP.systemid=PS.id
		WHERE OP.type>=100 AND OP.type<200 AND OP.systemid<>1 AND OP.systemid<>2
	GROUP BY PS.name
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getBalance]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getBalance]
	-- user name
	@user varchar(80),
	-- service id
    @svcid    int,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	SET NOCOUNT ON;
	
	DECLARE @USERID INT;
	declare @partnerId int
    -- check parameters
	IF @USER IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END

	--check subscription, and auto-subscription
	if ( @ERROR = 0 )
	BEGIN
	declare @active bit
	SELECT @active = active FROM UserServices 
			WHERE userid = @USERID AND serviceid = @svcid;
		IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
		BEGIN
			declare @template xml
			SELECT @template = PARAMETERS FROM DBO.TEMPLATES WHERE isnull(partnerId, 0) = isnull(@partnerId, 0)
			if (@template.exist('/template/service[id=sql:variable("@svcid")]') = 1)
			BEGIN
				declare @errorInSubscribe int
				select @errorInSubscribe = 0
				EXEC dbo.sp_int_subscribeUser	@USERID = @userid, -- int
												@SERVICEID = @svcid, -- int
												@password = NULL, -- varbinary(80)
												@error =  @errorInSubscribe OUTPUT -- int
				if (@errorInSubscribe <> 0)
					select @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END
			else
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		END
	END

	IF @error <> 0
		RETURN -1;
	
	DECLARE @cbtpsid INT;
	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();

	DECLARE @amount DECIMAL(15, 2);

	IF @svcid IS NULL
		SELECT @amount=SUM(amount) FROM dbo.VW_UserBalance WHERE id = @userid AND systemid <>@cbtpsid		
	ELSE
	BEGIN
		DECLARE @opid INT;
		DECLARE @cbtmode BIT;

		SELECT @opid=opid, @cbtmode=cbtMode FROM dbo.vw_api_accountMap WHERE userId = @USERID AND serviceId = @svcid
		
		IF @opid IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		
		IF @error <> 0
			RETURN -1;	

		if 	@cbtmode = 0
			SELECT @amount = SUM(sa.amount) 
			FROM dbo.SubAccounts sa
			inner join PaymentSystems ps
			on sa.systemid = ps.id
			WHERE sa.accid = @opid AND sa.systemid <> @cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)
		else
			SELECT @amount = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @opid AND systemid = @cbtpsid
	END	

	IF @amount IS NULL
		SET @amount=0;
	
	declare @reservedAmount decimal
	select @reservedAmount = sum(amount) from WriteOffReserve 
	where accountId = @opid and cbt = @cbtmode and finishTime > GETDATE()

	--temp logging
--	DECLARE @content VARCHAR(8000);
--	SELECT @content = 
--		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END
--		
--	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 550, 
--			@serviceid=@svcid, @userid = @USERID, @amount = @amount, 
--			@parameters = @content, @error = @error OUTPUT
	--/temp logging	


	SELECT ( @amount - isnull(@reservedAmount, 0) ) AS AMOUNT;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getWriteOffDetails]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getWriteOffDetails]
	-- user name
	@user varchar(80) = NULL,
	-- operation id
	@operationid int,
	-- error code
	@error int OUTPUT
AS
BEGIN
	-- check user
	SET @error = 0;
	
	DECLARE @userid int;
	
	-- check user
	IF @user IS NULL
		SET @userid = NULL
	ELSE
	BEGIN
		SELECT @userid = id FROM Users WHERE Users.name = @user;
		IF @userid IS NULL
			SET @error = dbo.sf_int_get_error_code('E_INVALID_USER');
	END

	-- check operation + user
	IF NOT @userid IS NULL
	BEGIN
		IF (SELECT COUNT(*) FROM Operations WHERE userid = @userid AND id = @operationid) = 0
			SET @error = dbo.sf_int_get_error_code('E_INVALID_ARG');
	END
	
	IF @error <>0
		RETURN -1;	
	
	SELECT
		o.id AS OperationId,
		o.userid AS UserId,
		o.serviceid AS ServiceId,
		s.name AS Service,
		o.amount AS OperationAmount,
		o.executedat AS OperationDate,
		wo.amount AS WriteOffAmount,
		wo.paymentSystemId AS PaymentSystemId,
		ps.name AS PaymentSystemName	
	FROM 
		Operations AS o INNER JOIN
		WriteOffsPaymentSystem AS wo ON o.id = wo.operationId LEFT JOIN
		PaymentSystems AS ps ON ps.id = wo.paymentSystemId LEFT JOIN
		[Services] AS s ON s.id = o.serviceid
	WHERE
		o.id = @operationid;
		
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getTransactionsByUsername]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/27
-- Update 1: 2010/05/03
-- Description:	Gets transactions by username

CREATE PROCEDURE [dbo].[sp_rpt_getTransactionsByUsername]
	-- username
	@username VARCHAR(80),
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- list of systems
	@systemIdList VARCHAR(8000) = NULL
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	-- temp table
	DECLARE @pSystemsID AS TABLE
	(
		systemID INT
	)
		
	-- fill payment systems
	IF (NOT @systemIdList IS NULL)
	BEGIN
		INSERT INTO @pSystemsID (systemID)
			SELECT CAST(part AS INT) FROM [sf_int_split](@systemIdList,',')
	END
	ELSE
		INSERT INTO @pSystemsID (systemID)
			SELECT id FROM dbo.PaymentSystems
			WHERE id<>1 AND id<>2

		
	SELECT  OP.executedat AS Date, OP.amount AS Amount, PS.name AS PaymentSystem
	FROM dbo.Operations AS OP
		INNER JOIN dbo.PaymentSystems AS PS ON OP.systemid=PS.id
		INNER JOIN dbo.Users AS US ON OP.userid=US.name
		WHERE OP.type>=100 AND OP.type<200 AND 
			OP.systemid<>1 AND OP.systemid<>2
			AND OP.executedat BETWEEN @fDate AND @tDate
			AND US.name=@username
			AND OP.systemid IN (SELECT * FROM @pSystemsID)
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getPaymentsHistory]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/15
-- Description:	Retrieves payments history

CREATE PROCEDURE [dbo].[sp_api_getPaymentsHistory]
	-- user name
	@user varchar(80),
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	DECLARE @USERID INT;
	
	-- check parameters
    IF @USER IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
	
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END
	
	IF @ERROR <> 0
		RETURN -1;

	SELECT OP.AMOUNT, OP.EXECUTEDAT, PS.ID AS SYSTEMID, PS.NAME AS PAYMENTSYSTEM FROM DBO.OPERATIONS AS OP, dbo.PaymentSystems AS PS
			WHERE type>=100 AND type<200 AND EXECUTEDAT BETWEEN @fDate AND @tDate AND PS.id = OP.systemid AND OP.userid = @USERID
			ORDER BY OP.executedat ASC
	RETURN 0;
END
GO
/****** Object:  View [dbo].[vw_gui_protocolPaymentSystems]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_gui_protocolPaymentSystems]
AS
SELECT     dbo.PaymentSystems.id, dbo.PaymentSystems.name, CASE WHEN dbo.ProtocolPaymentSystems.systemid IS NULL 
                      THEN 0 ELSE 1 END AS protocol
FROM         dbo.PaymentSystems LEFT OUTER JOIN
                      dbo.ProtocolPaymentSystems ON dbo.PaymentSystems.id = dbo.ProtocolPaymentSystems.systemid
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "PaymentSystems"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 114
               Right = 189
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "ProtocolPaymentSystems"
            Begin Extent = 
               Top = 6
               Left = 227
               Bottom = 69
               Right = 378
            End
            DisplayFlags = 280
            TopColumn = 0
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
      Begin ColumnWidths = 9
         Width = 284
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_protocolPaymentSystems'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_protocolPaymentSystems'
GO
/****** Object:  View [dbo].[vw_gui_Payments]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_gui_Payments]
AS
SELECT     OP.userid AS UserID, OP.executedat AS Date, OP.amount AS Amount, PS.name AS PaymentSystem, OP.reason AS Reason
FROM         dbo.Operations AS OP LEFT OUTER JOIN
                      dbo.PaymentSystems AS PS ON OP.systemid = PS.id
WHERE     (OP.userid IS NOT NULL) AND (OP.type >= 100) AND (OP.type < 200)
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[41] 4[20] 2[9] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "PS"
            Begin Extent = 
               Top = 6
               Left = 227
               Bottom = 114
               Right = 378
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "OP"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 114
               Right = 189
            End
            DisplayFlags = 280
            TopColumn = 0
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
      Begin ColumnWidths = 9
         Width = 284
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_Payments'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_Payments'
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getValuePSDetailed]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getValuePSDetailed]
    @svcid int,
	@user varchar(80),
	@ps varchar(80),
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	SET NOCOUNT ON;
	
	IF @user IS NULL or not (@ps in ('dedicated', 'bonuses', 'real'))
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END

	declare @userid INT;
	SELECT @userid = ID FROM USERS WHERE USERS.NAME = @user;
	IF @userid IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		RETURN -1
	END

	declare @opid int
	declare @cbtmode bit
	SELECT @opid = opid, @cbtmode = cbtMode FROM dbo.vw_api_accountMap WHERE userId = @USERID AND serviceId = @svcid
	
	if (@opid is null)
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		RETURN -1
	END

	DECLARE @amountPS DECIMAL(15, 2);

	if (@ps = 'dedicated')
	BEGIN
		declare @dedicatedPSId int
		select @dedicatedPSId = id from PaymentSystems where ownSvcId = @svcid
		
		SELECT @amountPS = SUM(amount) FROM dbo.SubAccounts 
			WHERE accid = @opid and systemid = @dedicatedPSId
			
	END
	else if (@ps = 'bonuses')
	BEGIN
		declare @bonusPSId int
		select @bonusPSId = dbo.sf_int_get_bonuses_ps();

		SELECT @amountPS = SUM(amount) FROM dbo.SubAccounts 
			WHERE accid = @opid and systemid = @bonusPSId
	END
	else if (@ps = 'real')
	BEGIN
		SELECT @amountPS = SUM(sa.amount) 
			FROM dbo.SubAccounts sa
			inner join PaymentSystems ps
			on sa.systemid = ps.id
			WHERE sa.accid = @opid AND ps.priority >= 2
	END

--	
--	IF (@USER IS NULL)
--	BEGIN --общий баланс awardMoney
--		select @awardAmount = SUM(amount) FROM dbo.SubAccounts 
--				WHERE systemId = @awardpsid
--
--		IF @awardAmount IS NULL
--			SET @awardAmount = 0;
--		SELECT @awardAmount AS AwardAmount;
--		return 0;
--	END
--	ELSE --award баланс юзера на всех счетах 
--	BEGIN
--		-- resolve user id
--		IF @ERROR = 0
--		BEGIN
--			SELECT @USERID = ID, @mainAccId = accid FROM USERS WHERE USERS.NAME = @USER;
--			IF @USERID IS NULL
--				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
--		END
--
--		IF @error <> 0
--		RETURN -1;
--
--		select @awardAmount = SUM(amount) FROM dbo.SubAccounts 
--				WHERE systemId = @awardpsid	and accid in
--					(select @mainAccId union select accountid from UserServices where userid = @USERID)	
--
--		IF @awardAmount IS NULL
--			SET @awardAmount = 0;
--		
		SELECT @amountPS AS amountPS;

		RETURN 0;
--	END
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_adminWriteOff]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_adminWriteOff]
	@EMPID INT,
	@USERID INT,
	@ACCID INT,
	@AMOUNT decimal(15,2),
	@SYSTEMID INT,
	@REASON text,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @cbtpsid INT; 
	DECLARE @balance decimal(15,2); 

	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();
	
	IF  @USERID IS NULL OR @ACCID IS NULL OR @AMOUNT IS NULL OR @AMOUNT<=0
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END 


	BEGIN TRANSACTION T_ADMIN_WRITEOFF
	
	-- check balance
	IF @ERROR = 0
	BEGIN
		-- get current balance
		IF NOT @SYSTEMID IS NULL
			SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid = @SYSTEMID
		else
			SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid <> @cbtpsid

		EXEC dbo.sp_int_trace 'Current balance by system id', @balance,@SYSTEMID 
		
		if (@balance IS NULL or @balance < @AMOUNT)
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
	END
    
    -- register operation
    IF @ERROR = 0
	BEGIN
    
        EXEC dbo.sp_int_trace 'Try to create new operation', @balance
    
		-- INSERT  NEW OPERATION ===========================
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, SRCACCID, EMPID, REASON)
			VALUES (@AMOUNT, @USERID, GETDATE(), 202, @ACCID, @EMPID, @REASON)
		
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END

	-- write-off
	IF @ERROR = 0
	BEGIN
		DECLARE @AMTWK decimal(15,2);
		SET @AMTWK = @AMOUNT;
		DECLARE @SID INT, @SAMMOUNT decimal(15,2), @SSYSTEMID INT;


		WHILE(@ERROR = 0 AND @AMTWK > 0)
		BEGIN
            -- select subaccounts
			SELECT TOP 1 @SID = SC.ID, @SAMMOUNT = SC.AMOUNT, @SSYSTEMID = SC.SYSTEMID from dbo.SubAccounts AS SC, dbo.PaymentSystems as PS	
				WHERE SC.AMOUNT > 0 AND SC.ACCID = @ACCID AND SC.SYSTEMID = PS.ID AND 
					 ((@SYSTEMID IS NULL AND SYSTEMID<>@cbtpsid) OR (NOT @SYSTEMID IS NULL AND SYSTEMID=@SYSTEMID))
				ORDER BY PS.priority ASC
            
                        
           	IF (@SID IS NULL)
            	SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
            
            IF @error=0
            BEGIN
                DECLARE @ToWriteOff decimal(15,2);
                IF @AMTWK < @SAMMOUNT
                    SELECT @ToWriteOff = @AMTWK;
                ELSE
                    SELECT @ToWriteOff = @SAMMOUNT;                     
                
                EXEC dbo.sp_int_trace 'Try to write off: SCCID, AMOUNT, SYSTEMID', @SID, @ToWriteOff, @SSYSTEMID

            	EXEC dbo.sp_int_writeOff_acc_sub @OPERID, @SID, @ToWriteOff, @error OUTPUT;
				
				--add record for royalty calculation
				INSERT WriteOffsPaymentSystem(operationId, paymentSystemId, amount)
					VALUES (@OPERID, @SYSTEMID, @ToWriteOff)
               
                IF @ERROR = 0
                BEGIN
                    SELECT @AMTWK = @AMTWK - @ToWriteOff;
                    EXEC dbo.sp_int_trace 'Still to write off', @AMTWK  
                END
            END         			
		END
	END


	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_ADMIN_WRITEOFF
		RETURN 0;
	END
	
	ROLLBACK TRANSACTION T_ADMIN_WRITEOFF 
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getActualBalanceFiltered]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_gui_getActualBalanceFiltered] 
	@userID INT,
	@serviceID int
AS
BEGIN
	SET NOCOUNT ON;
	--declare @cbtPs int

	declare @cbtPs int;
	select @cbtPs = cast([value] as int) from dbo.Settings where name = 'PAYMENT.SYSTEM.CBT.ID';

	select @userID as UserID,
	sa.systemid as PaymentSystemID, ps.[name] as PaymentSystemName, sa.amount as Amount--, sa.accid, us.serviceid
	FROM dbo.SubAccounts sa inner join Accounts acc ON sa.accid = acc.id
	inner join PaymentSystems ps on sa.systemid = ps.id 
	left join UserServices us on sa.accid = us.accountid
		where acc.userid = @userID
			and sa.systemid <> @cbtPs
			and ((us.serviceid is null and @serviceID = 0) or (us.serviceid = @serviceID))
			and sa.amount > 0
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getRealPaymentSystems]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 31/03/2010
-- Description:	Gets AccountCBT details
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_getRealPaymentSystems] 
	@userID INT
AS
BEGIN
	SET NOCOUNT ON;

	 SELECT DISTINCT systemid, dbo.PaymentSystems.name 
	 FROM dbo.SubAccounts, dbo.Accounts, dbo.PaymentSystems 
	 WHERE accid = dbo.Accounts.id
		AND userid =@userID 
		AND systemid = dbo.PaymentSystems.id 
		AND systemid<>1 AND systemid<>2
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getPaymentsHistory]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/09
-- Description:	Retrieves payments history

CREATE PROCEDURE [dbo].[sp_gui_getPaymentsHistory]
	-- user name
	@userID INT,
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- from amount
	@fromAmount DECIMAL,
	-- to amount
	@toAmount DECIMAL,
	-- payment system
	@paymentSystem VARCHAR(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	DECLARE @fAmount DECIMAL;
	DECLARE @tAmount DECIMAL;
	DECLARE @count INT;
	
	-- check parameters
    IF @UserID IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	SET @fAmount=@fromAmount;
	SET @tAmount=@toAmount;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @count=COUNT(*) FROM Users WHERE id=@userID
		IF @count=0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END
	
	IF @ERROR <> 0
		RETURN -1;
	IF( LEN(@paymentSystem)>0)
	BEGIN
		SELECT OP.AMOUNT, OP.EXECUTEDAT, PS.ID AS SYSTEMID, PS.NAME AS PAYMENTSYSTEM, OP.reason AS REASON FROM DBO.OPERATIONS AS OP, dbo.PaymentSystems AS PS
				WHERE PS.name=@paymentSystem AND type>=100 AND type<200 
					AND EXECUTEDAT BETWEEN @fDate AND @tDate AND PS.id = OP.systemid 
					AND OP.userid = @userID
					AND OP.amount BETWEEN @fAmount AND @tAmount
				ORDER BY OP.executedat ASC
	END		
	ELSE
	BEGIN
		SELECT OP.AMOUNT, OP.EXECUTEDAT, PS.ID AS SYSTEMID, PS.NAME AS PAYMENTSYSTEM, OP.reason AS REASON FROM DBO.OPERATIONS AS OP, dbo.PaymentSystems AS PS
				WHERE type>=100 AND type<200 
					AND EXECUTEDAT BETWEEN @fDate AND @tDate AND OP.systemid !=1 AND OP.systemid!=2
					AND PS.id = OP.systemid 
					AND OP.userid = @userID
					AND OP.amount BETWEEN @fAmount AND @tAmount
				ORDER BY OP.executedat ASC
	END
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_writeOffmigr]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Writes-off 
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_writeOffmigr]
	@SVCID	INT,
	@USERID INT,
	@ACCID INT,
	@AMOUNT decimal(15,2),
	@TYPE INT,
	@REASON text,
	@cbt bit,
	@executedate datetime,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @cbtpsid INT; 
	DECLARE @balance decimal(15,2); 

	SET @cbtpsid = 2;
	
--	IF  @USERID IS NULL OR @ACCID IS NULL OR @AMOUNT IS NULL OR @AMOUNT<=0
--	BEGIN
--		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
--		RETURN -1;
--	END 
	-- check for fraud
--	IF @error = 0
--	BEGIN
--		EXEC dbo.sp_int_checkFraudWriteOff @amount = @AMOUNT, -- decimal
--		    @svcid = @SVCID, -- int
--		    @userid = @USERID, -- int
--		    @error = @error OUTPUT -- int
--	END
	
--	BEGIN TRANSACTION T_WRITEOFF
--	
--	if 	@cbt = 0
	--SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid <> @cbtpsid
--	else
--		SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid = @cbtpsid

	--EXEC dbo.sp_int_trace 'Current balance', @balance

--	IF @ERROR = 0
--	BEGIN
	--	if (@balance IS NULL or @balance<@AMOUNT)
	--		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
--	END
    
    IF @ERROR = 0
	BEGIN
    
        --EXEC dbo.sp_int_trace 'Try to create new operation', @balance
    
		-- INSERT  NEW OPERATION ===========================
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, SRCACCID, SERVICEID, REASON)
			VALUES (@AMOUNT, @USERID, @executedate, @TYPE, @ACCID, @SVCID, @REASON)
		
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END

	IF @ERROR = 0
	BEGIN
		DECLARE @AMTWK decimal(15,2);
		SET @AMTWK = @AMOUNT;
		DECLARE @SID INT, @SAMMOUNT decimal(15,2), @SYSTEMID INT;


		WHILE( @AMTWK > 0 AND @ERROR=0)
		BEGIN
            
			SELECT TOP 1 @SID = SC.ID, @SAMMOUNT = SC.AMOUNT, @SYSTEMID = SC.SYSTEMID from dbo.SubAccounts AS SC, dbo.PaymentSystems as PS	
				WHERE SC.AMOUNT > 0 AND SC.ACCID = @ACCID AND SC.SYSTEMID = PS.ID AND 
					 ((@cbt=0 AND SYSTEMID<>@cbtpsid) OR (@cbt<>0 AND SYSTEMID=@cbtpsid))
				ORDER BY PS.priority ASC
            
                        
           	IF (@SID IS NULL)
            	SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
            
            IF @error=0
            BEGIN
                DECLARE @ToWriteOff decimal(15,2);
                IF @AMTWK < @SAMMOUNT
                    SELECT @ToWriteOff = @AMTWK;
                ELSE
                    SELECT @ToWriteOff = @SAMMOUNT;                     
                
                --EXEC dbo.sp_int_trace 'Try to write off: sub account/amount/systemid', @SID, @ToWriteOff, @SYSTEMID 
				---work over
				--EXEC dbo.sp_int_writeOff_acc_sub @OPERID, @SID, @ToWriteOff, @error OUTPUT;
				--@OPERID INT,
				-- sub account id
				--@SUBACCID INT,
				-- ammount of operation
				--@AMOUNT decimal(15,2),
				-- error code
				--@error int OUTPUT

				-- CHANGE BALANCE =============================    
				UPDATE DBO.SUBACCOUNTS
					SET AMOUNT = AMOUNT - @ToWriteOff 
					WHERE ID = @SID 
				-- INSERT TRANSACTION =========================
				INSERT INTO dbo.Transactions (operationid, subaccid, amount)
					VALUES (@OPERID, @SID, @AMOUNT)
				--end work over
				
				--add record for royalty calculation
				INSERT WriteOffsPaymentSystem(operationId, paymentSystemId, amount)
					VALUES (@OPERID, @SYSTEMID, @ToWriteOff)
               
                IF @ERROR = 0
                BEGIN
                    SELECT @AMTWK = @AMTWK - @ToWriteOff;
                    --EXEC dbo.sp_int_trace 'Still to write off', @AMTWK  
                END
            END         			
		END
	END


--	IF @ERROR = 0
--	BEGIN
--		COMMIT TRANSACTION T_WRITEOFF
--		RETURN 0;
--	END
--	
--	ROLLBACK TRANSACTION T_WRITEOFF 
--	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_transferMigr]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/11
-- Description:	Does internal processing of money transfer 
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_transferMigr]
	@USERID INT,
	@SRCACCID INT,
    @DSTACCID INT,
	@AMOUNT decimal(15,2),
	@TYPE INT,
	@REASON text,
	@cbt bit,
	@operdate datetime,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @cbtpsid INT; 
	DECLARE @balance decimal(15,2); 

	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();
	
	BEGIN TRANSACTION T_TRANSFER
	
	if 	@cbt=0
		SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @SRCACCID AND systemid <> @cbtpsid
	else
		SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @SRCACCID AND systemid = @cbtpsid

	IF @ERROR = 0
	BEGIN
        --EXEC dbo.sp_int_trace 'Current balance', @balance
                
		if (@balance IS NULL or @balance<@AMOUNT)
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
	END
    
    IF @ERROR = 0
	BEGIN
    
        --EXEC dbo.sp_int_trace 'Try to create new operation', @balance
    
		-- INSERT  NEW OPERATION ===========================
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, SRCACCID, DESTACCID, REASON)
			VALUES (@AMOUNT, @USERID, @operdate, @TYPE, @SRCACCID, @DSTACCID, @REASON)
		
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END

	IF @ERROR = 0
	BEGIN
		DECLARE @AMTWK decimal(15,2);
		SET @AMTWK = @AMOUNT;
		DECLARE @SCR_SUBACCID INT, @SRC_SUBAMMOUNT decimal(15,2), @SRC_SYSTEMID INT;


		WHILE( @AMTWK > 0 AND @ERROR=0)
		BEGIN
            
			SELECT @SCR_SUBACCID = NULL;

			SELECT TOP 1 @SCR_SUBACCID = SC.ID, @SRC_SUBAMMOUNT = SC.AMOUNT, @SRC_SYSTEMID = SC.SYSTEMID 
            	from dbo.SubAccounts AS SC, dbo.PaymentSystems as PS	
				WHERE SC.AMOUNT > 0 AND SC.ACCID = @SRCACCID AND SC.SYSTEMID = PS.ID AND 
					 ((@cbt=0 AND SYSTEMID<>@cbtpsid) OR (@cbt<>0 AND SYSTEMID=@cbtpsid))
				ORDER BY PS.priority ASC
            
			--EXEC dbo.sp_int_trace 'State @SCR_SUBACCID, @SRC_SUBAMMOUNT', @SCR_SUBACCID, @SRC_SUBAMMOUNT
                        
           	IF (@SCR_SUBACCID IS NULL)
            BEGIN
            	--EXEC dbo.sp_int_trace 'Unable to get sub account id for', @SRCACCID
            	SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END                
            
            DECLARE @ToWriteOff decimal(15,2);
            
            IF @error=0
            BEGIN
                
				--EXEC dbo.sp_int_trace 'Try to write off. @AMTWK, @SRC_SUBAMMOUNT  ', @AMTWK, @SRC_SUBAMMOUNT

                IF @AMTWK<@SRC_SUBAMMOUNT
                    SELECT @ToWriteOff = @AMTWK;
                ELSE
                    SELECT @ToWriteOff = @SRC_SUBAMMOUNT;                     
                
                --EXEC dbo.sp_int_trace 'Try to write off. SRC SUB ACCID, AMMOUNT ', @SCR_SUBACCID, @ToWriteOff

            	EXEC dbo.sp_int_writeOff_acc_sub @OPERID, @SCR_SUBACCID, @ToWriteOff, @error OUTPUT;
           END
           
           IF @error=0
           BEGIN    
           		--EXEC dbo.sp_int_trace 'Try to replanish. DEST ACCID, AMMOUNT ', @DSTACCID, @ToWriteOff	
                EXEC [dbo].[sp_int_replenish_acc]  @OPERID, @DSTACCID, @SRC_SYSTEMID, @ToWriteOff, @error OUTPUT ;
 		   END              
               
           IF @ERROR = 0
           BEGIN
           		SELECT @AMTWK = @AMTWK - @ToWriteOff;
                --EXEC dbo.sp_int_trace 'Still to transfer', @AMTWK  
           END         			
		END
	END


	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_TRANSFER
		RETURN 0;
	END
	
	ROLLBACK TRANSACTION T_TRANSFER 
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_transfer]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_transfer]
	@USERID INT,
	@SRCACCID INT,
    @DSTACCID INT,
	@AMOUNT decimal(15,2),
	@TYPE INT,
	@REASON text,
	@cbt bit,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @cbtpsid INT; 
	DECLARE @balance decimal(15,2); 

	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();
	
	BEGIN TRANSACTION T_TRANSFER
	
	if 	@cbt=0
		--SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @SRCACCID AND systemid <> @cbtpsid
		--т.к. переводить dedicated нельзя
		SELECT @balance = SUM(sa.amount) 
			FROM dbo.SubAccounts sa
			inner join PaymentSystems ps
			on sa.systemid = ps.id
			WHERE sa.accid = @SRCACCID AND sa.systemid <> @cbtpsid and ps.ownSvcId is null
	else
		SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @SRCACCID AND systemid = @cbtpsid

	IF @ERROR = 0
	BEGIN
        EXEC dbo.sp_int_trace 'Current balance', @balance
                
		--учитываем резерв если имеется
		declare @reservedAmount decimal
		select @reservedAmount = sum(amount) from WriteOffReserve where accountId = @SRCACCID and cbt = @cbt

		if (@balance IS NULL or (@balance - isnull(@reservedAmount, 0)) < @AMOUNT)
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
	END
    
    IF @ERROR = 0
	BEGIN
    
        EXEC dbo.sp_int_trace 'Try to create new operation', @balance
    
		-- INSERT  NEW OPERATION ===========================
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, SRCACCID, DESTACCID, REASON)
			VALUES (@AMOUNT, @USERID, GETDATE(), @TYPE, @SRCACCID, @DSTACCID, @REASON)
		
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END

	IF @ERROR = 0
	BEGIN
		DECLARE @AMTWK decimal(15,2);
		SET @AMTWK = @AMOUNT;
		DECLARE @SCR_SUBACCID INT, @SRC_SUBAMMOUNT decimal(15,2), @SRC_SYSTEMID INT;


		WHILE( @AMTWK > 0 AND @ERROR=0)
		BEGIN
            
			SELECT @SCR_SUBACCID = NULL;
			--т.к. переводить dedicated нельзя
			SELECT TOP 1 @SCR_SUBACCID = SC.ID, @SRC_SUBAMMOUNT = SC.AMOUNT, @SRC_SYSTEMID = SC.SYSTEMID 
            	from dbo.SubAccounts AS SC, dbo.PaymentSystems as PS	
				WHERE SC.AMOUNT > 0 AND SC.ACCID = @SRCACCID AND SC.SYSTEMID = PS.ID AND 
					 ((@cbt=0 AND SYSTEMID<>@cbtpsid and ps.ownSvcId is null) OR (@cbt<>0 AND SYSTEMID=@cbtpsid))
				ORDER BY PS.priority ASC
            
			EXEC dbo.sp_int_trace 'State @SCR_SUBACCID, @SRC_SUBAMMOUNT', @SCR_SUBACCID, @SRC_SUBAMMOUNT
                        
           	IF (@SCR_SUBACCID IS NULL)
            BEGIN
            	EXEC dbo.sp_int_trace 'Unable to get sub account id for', @SRCACCID
            	SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END                
            
            DECLARE @ToWriteOff decimal(15,2);
            
            IF @error=0
            BEGIN
                
				--EXEC dbo.sp_int_trace 'Try to write off. @AMTWK, @SRC_SUBAMMOUNT  ', @AMTWK, @SRC_SUBAMMOUNT

                IF @AMTWK<@SRC_SUBAMMOUNT
                    SELECT @ToWriteOff = @AMTWK;
                ELSE
                    SELECT @ToWriteOff = @SRC_SUBAMMOUNT;                     
                
                EXEC dbo.sp_int_trace 'Try to write off. SRC SUB ACCID, AMMOUNT ', @SCR_SUBACCID, @ToWriteOff

            	EXEC dbo.sp_int_writeOff_acc_sub @OPERID, @SCR_SUBACCID, @ToWriteOff, @error OUTPUT;
           END
           
           IF @error=0
           BEGIN    
           		EXEC dbo.sp_int_trace 'Try to replanish. DEST ACCID, AMMOUNT ', @DSTACCID, @ToWriteOff	
                EXEC [dbo].[sp_int_replenish_acc]  @OPERID, @DSTACCID, @SRC_SYSTEMID, @ToWriteOff, @error OUTPUT ;
 		   END              
               
           IF @ERROR = 0
           BEGIN
           		SELECT @AMTWK = @AMTWK - @ToWriteOff;
                EXEC dbo.sp_int_trace 'Still to transfer', @AMTWK  
           END         			
		END
	END


	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_TRANSFER
		RETURN 0;
	END
	
	ROLLBACK TRANSACTION T_TRANSFER 
	RETURN -1
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_getBonusesRate]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does calculation of bonuses to full amount rate
-- =============================================
CREATE FUNCTION [dbo].[sf_int_getBonusesRate]()
RETURNS DECIMAL(15,2)
AS
BEGIN
	DECLARE @bonusesps INT
	DECLARE @cbtps INT
	DECLARE @bonuses DECIMAL(38,2)
	DECLARE @real DECIMAL(38,2)
	DECLARE @rate DECIMAL(15,2)
	
	SELECT @bonusesps = dbo.sf_int_get_bonuses_ps();
	SELECT @cbtps     = dbo.sf_int_get_cbt_ps();
	
	SELECT @bonuses = SUM(amount) FROM [dbo].[vw_UserBalance]
		WHERE systemid = @bonusesps;
	SELECT @real = SUM(amount) FROM [dbo].[vw_UserBalance]
		WHERE systemid <> @bonusesps AND systemid<>@cbtps;
	
	--EXEC dbo.sp_int_trace 'Current bonuses state', @bonuses, @real
	
	IF @bonuses IS NULL
		SELECT @bonuses = 0;
	IF @real IS NULL			
		SELECT @real = 0;	
	if (@bonuses = 0)
		RETURN 0;		
	IF (@real = 0)
		RETURN 9999999999999.99
	
	SET @rate = @bonuses/(@real+@bonuses)
	RETURN @rate;	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getPromocodes]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/04/28
-- Description:	Retrieves promocodes
-- =============================================

CREATE PROCEDURE [dbo].[sp_rpt_getPromocodes]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME,
	-- user name mask
	@userName VARCHAR(200),
	-- from amount
	@fromAmount INT,
	-- to amount
	@toAmount INT,
	-- reason
	@comment VARCHAR(200)
	
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');

	SELECT  dbo.Users.name AS UserName, 
		dbo.Operations.executedat AS Date, 
		dbo.Operations.amount AS Amount, 
		dbo.Operations.reason AS Reason
	FROM dbo.Promocodes, dbo.Users, dbo.Operations 
	WHERE dbo.Operations.executedat BETWEEN @fDate AND @tDate AND
	    dbo.Operations.id = dbo.Promocodes.operationid AND
		dbo.Operations.userid = dbo.Users.id AND
		dbo.Users.name LIKE @userName AND
		dbo.Operations.amount BETWEEN @fromAmount AND @toAmount AND
		dbo.Operations.reason LIKE @comment
	ORDER BY executedat


END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_setProtocolNodeSettings]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Andrey Limorov
-- Create date: 2010/03/18
-- Description:	Sets protocol settings
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_setProtocolNodeSettings]
	-- type of node: 101 service, 102 paymentsystem
	@type INT,
	-- service/ps id
	@id INT, 
	-- enable or disable protocol
	@enable BIT
AS
BEGIN
	IF (NOT @type BETWEEN 101 AND 102)
	    RAISERROR ('Invalid parameters',11,1);
	
	
	IF @type = 101
		BEGIN
			IF @enable = 1
				BEGIN
					IF NOT EXISTS (SELECT *  FROM ProtocolServices WHERE serviceid = @id)
						INSERT INTO ProtocolServices (serviceid) VALUES (@id);
				END			
			ELSE
				DELETE FROM ProtocolServices WHERE 	serviceid = @id;
			
			PRINT @@ERROR
			PRINT @@ROWCOUNT
			
		END
	ELSE			
		BEGIN
			IF @enable = 1
				BEGIN
					IF NOT EXISTS (SELECT *  FROM ProtocolPaymentSystems WHERE systemid = @id)
						INSERT INTO ProtocolPaymentSystems (systemid) VALUES (@id);
				END			
			ELSE
				DELETE FROM ProtocolPaymentSystems WHERE systemid = @id;

			PRINT @@ERROR
			PRINT @@ROWCOUNT

		END
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_subscribeUser]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/09
-- Description:	Does subscription of user for service
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_subscribeUser]
	@USERID INT,
	@SERVICEID INT,
	@password varbinary(80),
	@error int OUTPUT
AS
BEGIN
	SET @error = 0;
	
	-- check parameters	
	IF @USERID IS NULL OR @SERVICEID IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END 
		
	BEGIN TRANSACTION T_SUBSCIBE_SERVICE
	DECLARE @USID INT;
	DECLARE @USACTIVE BIT;

	SELECT @USID=ID, @USACTIVE=ACTIVE FROM USERSERVICES 
		WHERE USERID=@userid AND SERVICEID=@SERVICEID

	IF @USACTIVE = 1
	BEGIN
		EXEC dbo.sp_int_trace 'Service already subscriped',@USID ;
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ALREADY_SUBSCRIBED');
	END;

	IF @ERROR=0
	BEGIN
		IF NOT @USID IS NULL
			BEGIN
				EXEC dbo.sp_int_trace 'Re-subscribe service',@USID, @SERVICEID, @USERID, @password;
				UPDATE USERSERVICES SET USERSERVICES.active=1, USERSERVICES.password = @password WHERE ID = @USID
				IF @@ROWCOUNT = 0
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END
		ELSE
			BEGIN
				EXEC dbo.sp_int_trace 'Create new subscription',@SERVICEID, @USERID, @password;
				DECLARE @accid INT;
				EXECUTE @accid = dbo.sp_int_create_account @userid = @USERID
				INSERT INTO USERSERVICES (USERID,SERVICEID,BAN,ACCOUNTID,PASSWORD,ACTIVE) VALUES
					(@USERID, @SERVICEID,0,@ACCID,@PASSWORD,1)
				IF @@ERROR <> 0
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END
	END	

	if @ERROR<>0
		BEGIN
			ROLLBACK TRANSACTION T_SUBSCIBE_SERVICE;
			RETURN -1;
		END
	ELSE
		BEGIN
			COMMIT TRANSACTION T_SUBSCIBE_SERVICE;
			RETURN 0;
		END
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_addProtocolRecord]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/18
-- Description:	Does protocolling of parameters
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_addProtocolRecord]
	@typeid INT,
	
	@userid INT = NULL,
	@empid INT = NULL,
	@operationid INT = NULL,
	@serviceid INT = NULL,
	@systemid INT = NULL,

	@amount DECIMAL(15,2) = NULL,
	@result INT = NULL,
	@parameters TEXT = NULL,
	
	@error INT OUTPUT
	
AS
BEGIN
	SELECT @error = 0;
	
	IF (@typeid = 101 AND NOT EXISTS( SELECT * FROM dbo.ProtocolSettings, dbo.ProtocolServices WHERE dbo.ProtocolSettings.id = 101 AND dbo.ProtocolSettings.loglevel >= 2
		AND dbo.ProtocolServices.serviceid =@serviceid))
	BEGIN
		RETURN 0;
	END	
	
	EXEC dbo.sp_int_trace 'Try to add log record',@serviceid, @userid,@result
	
	INSERT INTO dbo.Protocols
		(occurredat, typeid, userid, empid, operationid, serviceid, systemid, amount, result, parameters)
	VALUES 
		(GETDATE(), @typeid, @userid, @empid, @operationid, @serviceid, @systemid, @amount, @result, @parameters);

	IF @@ERROR<>0
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		RETURN -1;
	END		
			
	RETURN 0;
END
GO
/****** Object:  View [dbo].[vw_gui_protocolServices]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_gui_protocolServices]
AS
SELECT     dbo.Services.id, dbo.Services.name, CASE WHEN dbo.ProtocolServices.serviceid IS NULL THEN 0 ELSE 1 END AS protocol
FROM         dbo.Services LEFT OUTER JOIN
                      dbo.ProtocolServices ON dbo.Services.id = dbo.ProtocolServices.serviceid
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "Services"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 154
               Right = 203
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "ProtocolServices"
            Begin Extent = 
               Top = 32
               Left = 329
               Bottom = 95
               Right = 480
            End
            DisplayFlags = 280
            TopColumn = 0
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
      Begin ColumnWidths = 9
         Width = 284
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_protocolServices'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_protocolServices'
GO
/****** Object:  StoredProcedure [dbo].[sp_int_cleanup_protocol]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/04/02
-- Description:	Does cleanup of protocols
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_cleanup_protocol]
AS
BEGIN
	EXECUTE dbo.sp_int_trace 'sp_int_cleanup_protocol'
	DECLARE @timeout INT;
	SET @timeout = NULL;

	DECLARE @point DATETIME;
	SET @point = DATEADD(hour,-1,GETDATE());
	DELETE FROM dbo.Protocols WHERE occurredat < @point AND typeid = 201
	
	
	SELECT @timeout = timeout FROM dbo.ProtocolSettings WHERE id = 101 ;
	IF @timeout IS NULL
		SET @timeout = 0;
	
	IF @timeout >= 0
	BEGIN
		SET @point = DATEADD(day,-@timeout,GETDATE());
		DELETE FROM dbo.Protocols WHERE occurredat < @point AND typeid IN (101, 102)
	END
	
	EXECUTE dbo.sp_int_trace 'sp_int_cleanup_protocol end'
	
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_setProtocolSettings]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Andrey Limorov
-- Create date: 2010/03/18
-- Description:	Sets protocol settings
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_setProtocolSettings]
	-- type of node: 101 service, 102 paymentsystem, 103 reporting
	@type INT,
	-- log level - 0 - off, 1 - on, 2 - log requests content
	@loglevel INT, 
	-- enable or disable protocol
	@timeout INT
AS
BEGIN
	IF (NOT @type IN (101, 102, 103)) OR NOT @loglevel BETWEEN 0 AND 2 OR @timeout<0
	BEGIN
	    RAISERROR ('Invalid parameters',11,1);
	    RETURN -1;
	END
	
	UPDATE dbo.ProtocolSettings SET loglevel = @loglevel, timeout = @timeout 
		WHERE id = @type;
		
	IF @@ROWCOUNT=0
	BEGIN
		RAISERROR ('Invalid ProtocolSettings table content',11,1);
		RETURN -1;
	END
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_replenishMigr]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_replenishMigr]
	@USERID INT,
	@ACCID INT,
	@PAYMENTSYSTEM INT,
	@AMOUNT DECIMAL(15,2),
	@TYPE INT,
	@REASON text,
	@CREATED datetime,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @SUBACCID INT;

	BEGIN TRANSACTION T_REPLENISH

	-- INSERT OPERATION ===========================
	IF @ERROR = 0
	BEGIN
		
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, DESTACCID, SYSTEMID, REASON)
			VALUES (@AMOUNT, @USERID, @CREATED, @TYPE, @ACCID, @PAYMENTSYSTEM, @REASON)
		IF @@ERROR <> 0
        BEGIN
--        	EXEC dbo.sp_int_trace 'Unable to create new operation', @@ERROR
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END            
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END
    
    IF @ERROR = 0
	BEGIN
    	EXEC [dbo].[sp_int_replenish_acc]  @OPERID, @ACCID, @PAYMENTSYSTEM, @AMOUNT, @error OUTPUT ;
	END
	
	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_REPLENISH
		RETURN 0;
	END
	ROLLBACK TRANSACTION T_REPLENISH
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getSvcsOnlyExists]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_gui_getSvcsOnlyExists]
	@userid varchar(80),
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
    -- check parameters
	if not exists (select id from Users where id = @userid)
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		return -1;
	END

	-- retrieve full services list with subscription marks
	select s.id AS SERVICEID, s.[name] AS SERVICENAME, us.ACTIVE AS SUBSCR from UserServices us
		inner join Services s on us.serviceid = s.id
		where userid = @userid

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getLastSession]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_gui_getLastSession] 
	@userID INT,
	@serviceID INT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	
	SELECT TOP 1 SV.name, PC.occurredat FROM dbo.Protocols AS PC
	INNER JOIN dbo.Services AS SV ON PC.serviceid = SV.id
	WHERE PC.typeid=501 AND PC.result=0 AND PC.userID=@userID AND @serviceID=PC.serviceID
	order by occurredat desc 
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getSubscribedIndepndentServices]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 01/04/2010
-- Description:	Gets subscribed independence services (for Game.aspx)
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_getSubscribedIndepndentServices]
	-- User ID
	@userID INT
AS
BEGIN
	SET NOCOUNT ON;

    SELECT SV.id, SV.name 
    FROM dbo.UserServices AS US
    INNER JOIN dbo.Services AS SV ON US.serviceid=SV.id
    WHERE US.userid=@userID AND SV.independent=1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getSubscribedServices]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 12/08/2010
-- Description:	Gets subscribed services (for Game.aspx)
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_getSubscribedServices]
	-- User ID
	@userID INT
AS
BEGIN
	SET NOCOUNT ON;

    SELECT SV.id, SV.name 
    FROM dbo.UserServices AS US INNER JOIN dbo.Services AS SV ON US.serviceid=SV.id
    WHERE US.userid=@userID
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_writeOffWithBalanceEx]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_writeOffWithBalanceEx]
	-- caller service id
	@svcid	int,
	-- user name
	@user varchar(80),
	-- account name
	@account varchar(50) = NULL,
	-- amount
	@amount decimal(15,2),
	-- reason of operation
	@reason text,
	--remained amount	
	@remainAmount decimal(15,2) OUTPUT,
	-- error code
	@error int OUTPUT
AS
BEGIN

	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	DECLARE @USERID INT;
	DECLARE @ACCOUNTID INT;
	DECLARE @MAINACCID INT;
	DECLARE @OPERID INT;
	declare @partnerId int;	

	-- check parameters
	IF  @SVCID IS NULL OR @USER IS NULL OR @amount IS NULL OR @amount<=0 OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 

	-- resolve user
	IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @MAINACCID = accid, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
	END
    
    DECLARE @cbtMode bit;
    --DECLARE @svcAccId INT;
        
    -- Resolve CBT mode ========================================================
    IF @ERROR = 0
	BEGIN
		SELECT @cbtMode = cbtMode FROM dbo.Services WHERE id = @svcid
		--SELECT @cbtMode = cbtMode
		--    FROM dbo.vw_api_accountMap 
		--    WHERE serviceId = @svcid and userid = @USERID;	
		--IF @cbtMode IS NULL
		--    SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
	END
        
	-- resolve account id
	IF NOT @ACCOUNT IS NULL -- account specified
		BEGIN
			SELECT @ACCOUNTID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @ACCOUNT;
			IF @ACCOUNTID IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
		END
	ELSE -- use account of service
		BEGIN
			declare @active bit
			SELECT @active = active FROM UserServices 
				WHERE userid = @USERID AND serviceid = @svcid
			IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
			BEGIN
				exec sp_int_autoSubscribe @svcid = @svcid, @userid = @userid, @partnerId = @partnerId, @error = @ERROR OUTPUT
			END

			IF (@ERROR = 0)
			BEGIN
				--SELECT @ACCOUNTID = @MAINACCID;
				SELECT @ACCOUNTID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@USERID;	
				IF @ACCOUNTID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END

			SELECT @ACCOUNTID = opId FROM dbo.vw_api_accountMap WHERE userid=@USERID AND serviceId=@svcid;
		END
	
	-- check account owner
	IF @ERROR = 0 AND @ACCOUNTID<>@MAINACCID
	BEGIN
		DECLARE @AOID INT;
		SELECT @AOID = DBO.SF_INT_RESOLVE_ACCOUNT_OWNER(@ACCOUNTID);
		IF @USERID <> @AOID
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
	END

	-- internal writeoff
	IF @ERROR = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Try to write-off: userid, accid, cbtMode', @USERID, @ACCOUNTID, @cbtMode
		EXEC DBO.sp_int_writeoffWithBalance @svcid, @USERID, @ACCOUNTID, @AMOUNT, 201, @REASON, @cbtMode, @remainAmount OUTPUT, @OPERID OUTPUT, @ERROR OUTPUT
	END
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_writeOff	@svcid = @svcid, -- int
								@userid = @USERID, -- int
								@amount = @AMOUNT, -- decimal
								@operationid = @OPERID, -- int
								@user = @user, -- varchar(80)
								@account = @account, -- varchar(50)
								@accid = @ACCOUNTID, -- int
								@reason = @REASON, -- text
								@state = @ERROR, -- int
								@error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================	
	
	IF @ERROR = 0
	BEGIN
		SELECT @OPERID AS OperationId;	
		RETURN 0;	
	END

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_writeOff]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_writeOff]
	-- caller service id
	@svcid	int,
	-- user name
	@user varchar(80),
	-- account name
	@account varchar(50) = NULL,
	-- amount
	@amount decimal(15,2),
	-- reason of operation
	@reason text,
	-- error code
	@error int OUTPUT
AS
BEGIN

	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	DECLARE @USERID INT;
	DECLARE @ACCOUNTID INT;
	DECLARE @MAINACCID INT;
	DECLARE @OPERID INT;
	DECLARE @partnerId int;
	
	-- check parameters
	IF  @SVCID IS NULL OR @USER IS NULL OR @amount IS NULL OR @amount<=0 OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 

	-- resolve user
	IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @MAINACCID = accid, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
	END
    
    DECLARE @cbtMode bit;
    --DECLARE @svcAccId INT;
        
    --check subscription, and auto-subscription
	--if ( @ERROR = 0 )
	--BEGIN
	--	declare @active bit
	--	SELECT @active = active FROM UserServices 
	--		WHERE userid = @USERID AND serviceid = @svcid;
	--	IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
	--	BEGIN
	--		declare @template xml
	--		SELECT @template = PARAMETERS FROM DBO.TEMPLATES WHERE isnull(partnerId, 0) = isnull(@partnerId, 0)
	--		declare @isInTemplate bit
	--		select @isInTemplate = @template.exist('/template/service[id=sql:variable("@svcid")]') 		
	--		if (@isInTemplate = 1)
	--		BEGIN
	--			declare @errorInSubscribe int
	--			select @errorInSubscribe = 0
	--			EXEC dbo.sp_int_subscribeUser	@USERID = @userid, -- int
	--											@SERVICEID = @svcid, -- int
	--											@password = NULL, -- varbinary(80)
	--											@error =  @errorInSubscribe OUTPUT -- int
	--			if (@errorInSubscribe <> 0)
	--				select @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	--		END
	--		else
	--			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
	--	END
	--END
	
	--Resolve CBT mode ========================================================
    IF @ERROR = 0
	BEGIN
		SELECT @cbtMode = cbtMode FROM dbo.Services WHERE id = @svcid
		--SELECT @cbtMode = cbtMode
		--    FROM dbo.vw_api_accountMap 
		--    WHERE serviceId = @svcid and userid = @USERID;	
		--IF @cbtMode IS NULL
		--    SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
	END
        
	IF ( @ERROR = 0 )
	BEGIN
		-- resolve account id
		IF NOT @ACCOUNT IS NULL -- account specified
			BEGIN
				SELECT @ACCOUNTID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @ACCOUNT;
				IF @ACCOUNTID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END
		ELSE -- use account of service
			BEGIN
				declare @active bit
				SELECT @active = active FROM UserServices 
					WHERE userid = @USERID AND serviceid = @svcid
				IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
				BEGIN
					exec sp_int_autoSubscribe @svcid = @svcid, @userid = @userid, @partnerId = @partnerId, @error = @ERROR OUTPUT
				END

				IF (@ERROR = 0)
				BEGIN
					--SELECT @ACCOUNTID = @MAINACCID;
					SELECT @ACCOUNTID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@USERID;	
					IF @ACCOUNTID IS NULL
						SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
				END

				SELECT @ACCOUNTID = opId FROM dbo.vw_api_accountMap WHERE userid=@USERID AND serviceId=@svcid;
			END
	END
	-- check account owner
	IF @ERROR = 0 AND @ACCOUNTID<>@MAINACCID
	BEGIN
		DECLARE @AOID INT;
		SELECT @AOID = DBO.SF_INT_RESOLVE_ACCOUNT_OWNER(@ACCOUNTID);
		IF @USERID <> @AOID
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
	END

	-- internal writeoff
	IF @ERROR = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Try to write-off: userid, accid, cbtMode', @USERID, @ACCOUNTID, @cbtMode
		EXEC DBO.sp_int_writeoff @svcid, @USERID, @ACCOUNTID, @AMOUNT, 201, @REASON, @cbtMode, @OPERID OUTPUT, @ERROR OUTPUT
	END
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_writeOff	@svcid = @svcid, -- int
								@userid = @USERID, -- int
								@amount = @AMOUNT, -- decimal
								@operationid = @OPERID, -- int
								@user = @user, -- varchar(80)
								@account = @account, -- varchar(50)
								@accid = @ACCOUNTID, -- int
								@reason = @REASON, -- text
								@state = @ERROR, -- int
								@error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_writeOffWithBalance]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_writeOffWithBalance]
	-- caller service id
	@svcid	int,
	-- user name
	@user varchar(80),
	-- account name
	@account varchar(50) = NULL,
	-- amount
	@amount decimal(15,2),
	-- reason of operation
	@reason text,
	--remained amount	
	@remainAmount decimal(15,2) OUTPUT,
	-- error code
	@error int OUTPUT
AS
BEGIN

	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	DECLARE @USERID INT;
	DECLARE @ACCOUNTID INT;
	DECLARE @MAINACCID INT;
	DECLARE @OPERID INT;
	declare @partnerId int;	

	-- check parameters
	IF  @SVCID IS NULL OR @USER IS NULL OR @amount IS NULL OR @amount<=0 OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 

	-- resolve user
	IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @MAINACCID = accid, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
	END
    
    DECLARE @cbtMode bit;
    --DECLARE @svcAccId INT;
        
    -- Resolve CBT mode ========================================================
    IF @ERROR = 0
	BEGIN
		SELECT @cbtMode = cbtMode FROM dbo.Services WHERE id = @svcid
		--SELECT @cbtMode = cbtMode
		--    FROM dbo.vw_api_accountMap 
		--    WHERE serviceId = @svcid and userid = @USERID;	
		--IF @cbtMode IS NULL
		--    SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
	END
        
	-- resolve account id
	IF NOT @ACCOUNT IS NULL -- account specified
		BEGIN
			SELECT @ACCOUNTID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @ACCOUNT;
			IF @ACCOUNTID IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
		END
	ELSE -- use account of service
		BEGIN
			declare @active bit
			SELECT @active = active FROM UserServices 
				WHERE userid = @USERID AND serviceid = @svcid
			IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
			BEGIN
				exec sp_int_autoSubscribe @svcid = @svcid, @userid = @userid, @partnerId = @partnerId, @error = @ERROR OUTPUT
			END

			IF (@ERROR = 0)
			BEGIN
				--SELECT @ACCOUNTID = @MAINACCID;
				SELECT @ACCOUNTID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@USERID;	
				IF @ACCOUNTID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END

			SELECT @ACCOUNTID = opId FROM dbo.vw_api_accountMap WHERE userid=@USERID AND serviceId=@svcid;
		END
	
	-- check account owner
	IF @ERROR = 0 AND @ACCOUNTID<>@MAINACCID
	BEGIN
		DECLARE @AOID INT;
		SELECT @AOID = DBO.SF_INT_RESOLVE_ACCOUNT_OWNER(@ACCOUNTID);
		IF @USERID <> @AOID
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
	END

	-- internal writeoff
	IF @ERROR = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Try to write-off: userid, accid, cbtMode', @USERID, @ACCOUNTID, @cbtMode
		EXEC DBO.sp_int_writeoffWithBalance @svcid, @USERID, @ACCOUNTID, @AMOUNT, 201, @REASON, @cbtMode, @remainAmount OUTPUT, @OPERID OUTPUT, @ERROR OUTPUT
	END
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_writeOff	@svcid = @svcid, -- int
								@userid = @USERID, -- int
								@amount = @AMOUNT, -- decimal
								@operationid = @OPERID, -- int
								@user = @user, -- varchar(80)
								@account = @account, -- varchar(50)
								@accid = @ACCOUNTID, -- int
								@reason = @REASON, -- text
								@state = @ERROR, -- int
								@error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getExpensesByGames_totals]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/05/03
-- Description:	Retrieves expenses by games
-- =============================================
CREATE PROCEDURE [dbo].[sp_rpt_getExpensesByGames_totals]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
	
AS
BEGIN

	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	IF @fromDate IS NULL
		SELECT @fromDate = CONVERT(DATETIME, '2000/01/01 00:00');
	
	IF @toDate IS NULL
		SELECT @toDate = CONVERT(DATETIME, '2100/01/01 00:00');	
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	


	--	create date groups table
	CREATE TABLE #DateGroups( startDate DATETIME, finishDate DATETIME, monthName VARCHAR(50))

	DECLARE @i INT;
	DECLARE @newDate DATETIME;

	SET @i = 0;

	WHILE (@fDate < @tDate)
	BEGIN
		SET @newDate = dateadd(day, 1, @fDate);
		SET @i = @i + 1;
		IF (@newdate >= @tdate)
			SET @newdate = @tdate;

		INSERT INTO #DateGroups
		VALUES ( @fdate, @newdate, DATENAME(day, @fdate)) 

		SET @fDate = @newdate;
	END
	
	DECLARE @sum FLOAT;
	SELECT @sum = SUM(amount) 
	FROM dbo.Operations, #DateGroups	
	WHERE type = '201' AND
		executedat BETWEEN startDate AND finishDate
		
	DECLARE @Results TABLE (Date DATETIME, SvcId INT, GameName NVARCHAR(80), Amount DECIMAL(15,2), Trend DECIMAL(15,2));
	
	-- insert amount by games
	INSERT INTO @Results (Date, SvcId, GameName, Amount)			
		SELECT 
			startDate AS Date,
			-1 AS SvcId,
			'По всем играм в оперировании' AS GameName, 
			SUM(amount) AS Amount
		FROM dbo.Operations, dbo.Services, #DateGroups 
		WHERE type = '201' AND
			dbo.Operations.serviceid = dbo.Services.id AND
			executedat BETWEEN startDate AND finishDate	  
		GROUP BY startDate;
	
	-- insert amount by all games	
	INSERT INTO @Results (Date, SvcId, GameName, Amount)			
		SELECT 
			startDate AS Date,
			dbo.Services.id AS SvcId,
			name AS GameName, 
			SUM(amount) AS Amount
		FROM dbo.Operations, dbo.Services, #DateGroups 
		WHERE type = '201' AND
			dbo.Operations.serviceid = dbo.Services.id AND
			executedat BETWEEN startDate AND finishDate	  
		GROUP BY dbo.Services.id, name, startDate;
	
	-- calculate trend for amount by all games	
	CREATE TABLE #TMP_DATA(X FLOAT, Y FLOAT);
	INSERT INTO #TMP_DATA
		SELECT  CAST(Date - @fromDate AS DECIMAL) AS X, Amount AS Y 
			FROM @Results
			WHERE SvcId = -1

	DECLARE @FullAmount Table(X FLOAT, Y FLOAT, YL FLOAT);
	INSERT @FullAmount 
		EXEC dbo.sp_int_linear_approximation;	
		
	DELETE FROM #TMP_DATA;
		
	UPDATE @Results SET Trend = (SELECT YL FROM @FullAmount WHERE CAST(Date - @fromDate AS DECIMAL) = X )
	WHERE SvcId = -1;
	DELETE FROM @FullAmount;
	
	-- calculate trends
	DECLARE S1 CURSOR FOR SELECT DISTINCT dbo.Services.id AS svcid
		FROM dbo.Operations, dbo.Services
		WHERE type = '201' AND	dbo.Operations.serviceid = dbo.Services.id AND executedat BETWEEN @fromDate AND @toDate
		
	OPEN S1
	DECLARE @svid DATETIME;
	FETCH NEXT FROM S1 INTO @svid
	WHILE @@FETCH_STATUS = 0 
	BEGIN
	
		INSERT INTO #TMP_DATA
			SELECT  CAST(Date - @fromDate AS DECIMAL) AS X, Amount AS Y 
				FROM @Results
				WHERE SvcId = @svid

		DECLARE @AmountOP Table(X FLOAT, Y FLOAT, YL FLOAT);
		INSERT @AmountOP 
			EXEC dbo.sp_int_linear_approximation;	
		
		--DROP TABLE #TMP_DATA;
		DELETE FROM #TMP_DATA;
		
		UPDATE @Results SET Trend = (SELECT YL FROM @AmountOP WHERE CAST(Date - @fromDate AS DECIMAL) = X )
		WHERE SvcId = @svid;
		    
		DELETE FROM @AmountOP;
		
		FETCH NEXT FROM S1 INTO @svid 
	END

	CLOSE S1;
	DEALLOCATE S1;
	
	SELECT * FROM @Results;

END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_banUser]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Bans user on service

CREATE PROCEDURE [dbo].[sp_api_banUser]
	-- user name, cannot be null
	@user varchar(80),
	-- service name, cannot be null
	@serviceName varchar(80),
	-- reason of operation, cannot be null
	@reason TEXT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	SELECT @error = 0;

	-- check parameters	
	IF @USER IS NULL OR @serviceName IS NULL OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- resolve service
	IF @ERROR = 0
    BEGIN
        SELECT @SERVICEID = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        IF @SERVICEID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @SERVICEID
    END

    IF @ERROR = 0
	BEGIN    
		EXEC dbo.sp_int_banUser @serviceid = @SERVICEID, -- int
		    @userid = @USERID, -- int
		    @reason = @reason, -- text
		    @error = @ERROR OUTPUT -- int
		
	END

		-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_banUser @svcid = @SERVICEID, -- int
	    @userid = @userid, -- int
	    @name = @user, -- varchar(80)
	    @serviceName = @serviceName, -- varchar(80)
	    @reason = @reason, -- text
	    @state = @ERROR, -- int
	    @error = @errlog OUTPUT -- int
	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	 
	-- end log request ============================================================================

	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_getLoginGameCount]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/04/26
-- Description:	Retrieves count of game logins

CREATE PROCEDURE [dbo].[sp_rpt_getLoginGameCount]
	-- from date
	@fromDate DATETIME,
	-- to date
	@toDate DATETIME
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	
	-- check parameters
		
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');
		
	DECLARE @totalCount AS INT;

	SET @totalCount=0;

	SELECT @totalCount=COUNT(*) FROM dbo.Protocols
	WHERE typeid=501 AND result=0 AND occurredat BETWEEN @fDate AND @tDate;
	
	--SELECT 'Всего' AS ServiceName, @totalCount AS LoginCount
	
	--UNION
    
	SELECT SV.name AS ServiceName, COUNT(PC.serviceid)AS LoginCount  FROM Protocols AS PC
	INNER JOIN dbo.Services AS SV ON PC.serviceid=SV.id
	WHERE typeid=501 AND result=0 AND occurredat BETWEEN @fDate AND @tDate
	GROUP BY SV.name 
	
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_setServiceSettings]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Retrieves service specific settings of user

CREATE PROCEDURE [dbo].[sp_api_setServiceSettings]
	-- user name, cannot be null
	@user varchar(80),
	-- service name, cannot be null
	@serviceName varchar(80),
	-- new specific password or NULL
	@password varbinary(80) = NULL,
	-- new specific settings or NULL
	@properties XML,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	SELECT @error = 0;

	-- check parameters	
	IF @USER IS NULL OR @serviceName IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- resolve service
	IF @ERROR = 0
    BEGIN
        SELECT @SERVICEID = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        IF @SERVICEID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @SERVICEID
    END

    IF @ERROR = 0
    BEGIN
		UPDATE DBO.USERSERVICES SET PASSWORD=@PASSWORD, PROPERTIES=@PROPERTIES
			WHERE USERID=@USERID AND SERVICEID = @SERVICEID AND ACTIVE = 1;

		IF @@ROWCOUNT = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Cannot find service settings', @userid, @SERVICEID, @@ERROR;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		END
	END		

	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	EXEC dbo.sp_log_setServiceSettings	@svcid = @SERVICEID, -- int
										@userid = @userid, -- int
										@user = @user, -- varchar(80)
										@serviceName = @serviceName, -- varchar(80)
										@password = @password, -- varbinary(80)
										@properties = @properties, -- xml
										@state = @ERROR, -- int
										@error = @errlog OUTPUT -- int
	 
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================
	
	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_subscribeUser]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/09
-- Description:	Does subscription of user for service
-- =============================================
CREATE PROCEDURE [dbo].[sp_api_subscribeUser]
	-- user name
	@userName VARCHAR(80),
	-- service name
	@serviceName VARCHAR(80),
	-- special password
	@password varbinary(80),
	-- result error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SET @error = 0;
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	-- check parameters	
	IF @userName IS NULL OR @serviceName IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @userName;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- resolve service
	IF @ERROR = 0
    BEGIN
        SELECT @SERVICEID = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        IF @SERVICEID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @SERVICEID
    END
    	
	IF @ERROR = 0
		EXEC dbo.sp_int_subscribeUser	@USERID = @userid, -- int
										@SERVICEID = @SERVICEID, -- int
										@password = @password, -- varbinary(80)
										@error =  @ERROR OUTPUT -- int
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_subscribeUser	@svcid = @SERVICEID, -- int
									@userid = @USERID, -- int
									@userName = @userName, -- varchar(80)
									@serviceName = @serviceName, -- varchar(80)
									@password = @password, -- varbinary(80)
									@state = @ERROR, -- int
									@error = @errlog OUTPUT -- int
	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================
	
	if @ERROR<>0
		RETURN -1;	
				
	SELECT dbo.Accounts.NAME AS ACCOUNT FROM dbo.Accounts, dbo.UserServices 
		WHERE  dbo.UserServices.serviceid = @SERVICEID AND dbo.UserServices.userid = @USERID AND dbo.UserServices.accountid = dbo.Accounts.id
			
	RETURN 0;

END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_transfer]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_transfer]
    -- caller service id
    @svcid    int,
    -- source user name
    @srcUser varchar(80),
    -- source account name
    @srcAccount varchar(50) = NULL,
    -- dest user name
    @dstUser varchar(80),
    -- dest account name
    @dstAccount varchar(50) = NULL,
    -- amount
    @amount decimal(15,2),
    -- reason of operation
    @reason text,
    -- error code
    @error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
    SELECT  @ERROR = 0;
    
    DECLARE @USERID INT;
    DECLARE @DSTUSERID INT;
    DECLARE @srcAccountID INT;
    DECLARE @destAccountID INT;
    DECLARE @operid INT;
	declare @srcUserPartnerId int
	declare @destUserPartnerId int
	declare @active bit
    
    -- check parameters
    IF  @svcid IS NULL OR @srcUser IS NULL OR @dstUser IS NULL OR @amount IS NULL OR @amount<0
    BEGIN
		EXEC dbo.sp_int_trace 'Detected invalid arguments of sp_api_transfer'
        SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
    END 

	-- resolve source user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID, @srcAccountID = accid, @srcUserPartnerId = partnerid FROM USERS WHERE USERS.NAME = @srcUser;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'Source user detected', @USERID, @srcAccountID 
    END

    -- resolve dest user
    IF @ERROR = 0
    BEGIN
        SELECT @DSTUSERID = ID, @destAccountID = accid, @destUserPartnerId = partnerid FROM USERS WHERE USERS.NAME = @dstUser;
        IF @DSTUSERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'Dest user detected', @DSTUSERID, @destAccountID 
    END
    
    SET @destAccountID = NULL;
    IF @ERROR = 0 
    BEGIN
		IF NOT @dstAccount IS NULL
		BEGIN
			SELECT @destAccountID = id FROM dbo.Accounts WHERE userid = @DSTUSERID AND name = @dstAccount;
			IF @destAccountID IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
		END
    END
    
    DECLARE @cbtMode bit;
    DECLARE @svcAccId INT;
        
    SET @srcAccountID = NULL;
    -- resolve source account id
    IF @ERROR = 0 
    BEGIN
		IF NOT @srcAccount IS NULL
		BEGIN
			SELECT @srcAccountID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @srcAccount;
			IF @srcAccountID IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
		END
		ELSE 
			--SELECT @srcAccountID = opId FROM dbo.vw_api_accountMap WHERE userid=@USERID AND serviceId=@svcid;
		BEGIN
			SELECT @active = active FROM UserServices 
				WHERE userid = @DSTUSERID AND serviceid = @svcid
			IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
			BEGIN
				exec sp_int_autoSubscribe @svcid = @svcid, @userid = USERID, @partnerId = @srcUserPartnerId, @error = @ERROR OUTPUT
			END

			IF (@ERROR = 0)
			BEGIN
				--SELECT @ACCOUNTID = @MAINACCID;
				SELECT @srcAccountID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@USERID;	
				IF @srcAccountID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END
		END
    END
    
    -- resolve dest account id
	SET @destAccountID = NULL;
    IF @ERROR = 0 
    BEGIN
		IF NOT @dstAccount IS NULL
		BEGIN
			SELECT @destAccountID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @dstAccount;
			IF @destAccountID IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
		END
		ELSE 
			--SELECT @destAccountID = opId FROM dbo.vw_api_accountMap WHERE userid=@DSTUSERID AND serviceId=@svcid;
		BEGIN
			SELECT @active = active FROM UserServices 
				WHERE userid = @DSTUSERID AND serviceid = @svcid
			IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
			BEGIN
				exec sp_int_autoSubscribe @svcid = @svcid, @userid = @DSTUSERID, @partnerId = @destUserPartnerId, @error = @ERROR OUTPUT
			END

			IF (@ERROR = 0)
			BEGIN
				--SELECT @ACCOUNTID = @MAINACCID;
				SELECT @destAccountID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@DSTUSERID;	
				IF @destAccountID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END
		END
    END
    
    -- Resolve CBT mode ========================================================
    IF @ERROR = 0
    BEGIN
		SELECT @cbtMode = cbtMode FROM dbo.Services WHERE dbo.Services.id = @svcid;
		IF @cbtMode IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		/*
			IF @cbtMode IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		*/
    END
    
    -- Check for self transfer
    IF @ERROR = 0 AND @destAccountID = @srcAccountID
    BEGIN
    	 EXEC dbo.sp_int_trace 'Detected attempt to self transfer money', @destAccountID	
    	 SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');	
    END
    
    /*
    IF @ERROR = 0
    BEGIN
        DECLARE @AOID INT;
        SELECT @AOID = DBO.SF_INT_RESOLVE_ACCOUNT_OWNER(@srcAccountID);
        IF @USERID <> @AOID
        BEGIN
        	EXEC dbo.sp_int_trace 'Detected attempt to transfer money from another''s account', @destAccountID
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
        END
    END
	*/
	
	-- check for fraud
	IF @error = 0
	BEGIN
		EXEC dbo.sp_int_checkFraudTransfer
			@amount = @AMOUNT, -- decimal
		    @svcid = @SVCID, -- int
		    @userid = @USERID, -- int
		    @error = @error OUTPUT -- int
	END
	
    IF @ERROR = 0
    BEGIN
        EXEC dbo.sp_int_trace 'Try to transfer: userid, src, dest', @USERID, @srcAccountID, @destAccountID 
        EXEC [dbo].[sp_int_transfer]  @USERID, @srcAccountID, @destAccountID, 
			@amount, 301, @REASON, @cbtMode, @operid OUTPUT, @error OUTPUT;
    END
    
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_transfer @svcid = @svcid, -- int
	    @userid = @USERID, -- int
	    @amount = @amount, -- decimal
	    @operationid = @operid, -- int
	    @srcaccid = @srcAccountID, -- int
	    @dstaccid = @destAccountID, -- int
	    @srcUser = @srcUser, -- varchar(80)
	    @srcaccount = @srcAccount, -- varchar(50)
	    @dstUser = @dstUser, -- varchar(80)
	    @dstaccount = @dstAccount, -- varchar(50)
	    @reason = @REASON, -- text
	    @state = @ERROR, -- int
	    @error = @errlog OUTPUT

	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================
	    
    IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_unbanUser]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Un-bans user on service

CREATE PROCEDURE [dbo].[sp_api_unbanUser]
	-- user name, cannot be null
	@user varchar(80),
	-- service name, cannot be null
	@serviceName varchar(80),
	-- reason of operation, cannot be null
	@reason TEXT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	SELECT @error = 0;

	-- check parameters	
	IF @USER IS NULL OR @serviceName IS NULL OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- resolve service
	IF @ERROR = 0
    BEGIN
        SELECT @SERVICEID = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        IF @SERVICEID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @SERVICEID
    END

    IF @ERROR = 0
    BEGIN
		BEGIN TRANSACTION T_UNBAN_USER;
	   
		DECLARE @USID INT;  
		-- check subscribtion   
		DECLARE @USACTIVE BIT;
		SELECT @USID = ID, @USACTIVE = ACTIVE FROM USERSERVICES 
			WHERE USERID=@userid AND serviceid = @SERVICEID;

		IF @USACTIVE IS NULL OR @USACTIVE <> 1
		BEGIN
			EXEC dbo.sp_int_trace 'Service un-subscriped', @userid, @SERVICEID;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		END;

		IF @ERROR=0
		BEGIN
			EXEC dbo.sp_int_trace 'Un-ban user on service', @userid, @SERVICEID, @USID;
			UPDATE USERSERVICES SET ban = 0, banReason = @reason WHERE ID = @USID
			IF @@ROWCOUNT = 0
			BEGIN
				EXEC dbo.sp_int_trace 'Cannot update user service record', @USID, @@ERROR;
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END
		END	
			
		if @ERROR<>0
			ROLLBACK TRANSACTION T_UNBAN_USER;
		ELSE
			COMMIT TRANSACTION T_UNBAN_USER;
	END

	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_unbanUser	@svcid = @SERVICEID, -- int
								@userid = @userid, -- int
								@name = @user, -- varchar(80)
								@serviceName = @serviceName, -- varchar(80)
								@reason = @reason, -- text
								@state = @ERROR, -- int
								@error = @errlog OUTPUT -- int
	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================
	
	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_recordWrongCrc]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_recordWrongCrc]
	@svcid int = null,	
	@serviceName varchar(80) = NULL,
	@content TEXT = NULL,
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	SELECT @svcid = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
	
	INSERT INTO dbo.Protocols
		(occurredat, typeid, userid, empid, operationid, serviceid, systemid, amount, result, parameters)
	VALUES 
		(GETDATE(), 650, null, null, null, @svcid, null, null, 0, @content);
		RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_removeAmountWithReal]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_removeAmountWithReal]
	-- caller service id
	@svcid	int,
	-- user name
	@user varchar(80),
	-- account name
	@account varchar(50) = NULL,
	-- amount
	@amount decimal(15,2),
	-- reason of operation
	@reason text,
	--amount of real return to kw
	@realAmount decimal(15,2) OUTPUT,
	-- error code
	@error int OUTPUT
AS
BEGIN

	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	DECLARE @USERID INT;
	DECLARE @ACCOUNTID INT;
	DECLARE @MAINACCID INT;
	DECLARE @OPERID INT;
	DECLARE @partnerId int;
	
	-- check parameters
	IF  @SVCID IS NULL OR @USER IS NULL OR @amount IS NULL OR @amount<=0 OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 

	-- resolve user
	IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @MAINACCID = accid, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
	END
    
    DECLARE @cbtMode bit;
    --DECLARE @svcAccId INT;
        
    --check subscription, and auto-subscription
	--if ( @ERROR = 0 )
	--BEGIN
	--	declare @active bit
	--	SELECT @active = active FROM UserServices 
	--		WHERE userid = @USERID AND serviceid = @svcid;
	--	IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
	--	BEGIN
	--		declare @template xml
	--		SELECT @template = PARAMETERS FROM DBO.TEMPLATES WHERE isnull(partnerId, 0) = isnull(@partnerId, 0)
	--		declare @isInTemplate bit
	--		select @isInTemplate = @template.exist('/template/service[id=sql:variable("@svcid")]') 		
	--		if (@isInTemplate = 1)
	--		BEGIN
	--			declare @errorInSubscribe int
	--			select @errorInSubscribe = 0
	--			EXEC dbo.sp_int_subscribeUser	@USERID = @userid, -- int
	--											@SERVICEID = @svcid, -- int
	--											@password = NULL, -- varbinary(80)
	--											@error =  @errorInSubscribe OUTPUT -- int
	--			if (@errorInSubscribe <> 0)
	--				select @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	--		END
	--		else
	--			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
	--	END
	--END
	
	--Resolve CBT mode ========================================================
    IF @ERROR = 0
	BEGIN
		SELECT @cbtMode = cbtMode FROM dbo.Services WHERE id = @svcid
		--SELECT @cbtMode = cbtMode
		--    FROM dbo.vw_api_accountMap 
		--    WHERE serviceId = @svcid and userid = @USERID;	
		--IF @cbtMode IS NULL
		--    SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
	END
        
	IF ( @ERROR = 0 )
	BEGIN
		-- resolve account id
		IF NOT @ACCOUNT IS NULL -- account specified
			BEGIN
				SELECT @ACCOUNTID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @ACCOUNT;
				IF @ACCOUNTID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END
		ELSE -- use account of service
			BEGIN
				declare @active bit
				SELECT @active = active FROM UserServices 
					WHERE userid = @USERID AND serviceid = @svcid
				IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
				BEGIN
					exec sp_int_autoSubscribe @svcid = @svcid, @userid = @userid, @partnerId = @partnerId, @error = @ERROR OUTPUT
				END

				IF (@ERROR = 0)
				BEGIN
					--SELECT @ACCOUNTID = @MAINACCID;
					SELECT @ACCOUNTID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@USERID;	
					IF @ACCOUNTID IS NULL
						SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
				END

				SELECT @ACCOUNTID = opId FROM dbo.vw_api_accountMap WHERE userid=@USERID AND serviceId=@svcid;
			END
	END
	-- check account owner
	IF @ERROR = 0 AND @ACCOUNTID<>@MAINACCID
	BEGIN
		DECLARE @AOID INT;
		SELECT @AOID = DBO.SF_INT_RESOLVE_ACCOUNT_OWNER(@ACCOUNTID);
		IF @USERID <> @AOID
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
	END

	-- internal writeoff
	IF @ERROR = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Try to write-off: userid, accid, cbtMode', @USERID, @ACCOUNTID, @cbtMode
		EXEC DBO.sp_int_removeAmountWithReal @svcid, @USERID, @ACCOUNTID, @AMOUNT, 201, @REASON, @cbtMode, @OPERID OUTPUT, @realAmount OUTPUT, @ERROR OUTPUT
	END
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.sp_log_writeOff	@svcid = @svcid, -- int
								@userid = @USERID, -- int
								@amount = @AMOUNT, -- decimal
								@operationid = @OPERID, -- int
								@user = @user, -- varchar(80)
								@account = @account, -- varchar(50)
								@accid = @ACCOUNTID, -- int
								@reason = @REASON, -- text
								@state = @ERROR, -- int
								@error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
		SET @error = @errlog;
	-- end log request ============================================================================
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getServiceGuidName]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getServiceGuidName]
	-- user name, cannot be null
	@userid int,
	@serviceName VARCHAR(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	declare @SERVICEID int
	SELECT @error = 0;

	-- check parameters	
	IF @userid IS NULL or @serviceName is NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END 
	
	IF @ERROR = 0
    BEGIN
        SELECT @SERVICEID = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        IF @SERVICEID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @SERVICEID
    END

	--check user and get partnerId
	IF @ERROR = 0
	BEGIN
		declare @partnerId int
		declare @name nvarchar(80)
		SELECT @name = [name], @partnerId = partnerid FROM USERS WHERE USERS.id = @userid;
		IF ( @name IS NULL )
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END	

	IF ( @ERROR = 0 )
	BEGIN
		declare @active bit
		SELECT @active = active FROM UserServices 
			WHERE userid = @USERID AND serviceid = @SERVICEID
		IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
		BEGIN
			exec sp_int_autoSubscribe 
				@svcid = @SERVICEID,
				@userid = @userid,
				@partnerId = @partnerId,
				@error = @ERROR OUTPUT
		END
	END

	-- get guidName
    IF ( @ERROR = 0 )
    BEGIN
		SELECT a.[name] as SERVICENAME from UserServices us inner join Accounts a on us.accountid = a.id	
			WHERE us.userid = @userid and us.serviceid = @SERVICEID

		IF @@ROWCOUNT = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Cannot find service guidName', @userid, @@ERROR;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
		END
	END

	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getExpensesHistory]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/15
-- Description:	Retrieves expenses history

CREATE PROCEDURE [dbo].[sp_api_getExpensesHistory]
	-- user name
	@user varchar(80),
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	DECLARE @fDate DATETIME;
	DECLARE @tDate DATETIME;
	DECLARE @USERID INT;
	
	-- check parameters
    IF @USER IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
	
	SET @fDate = @fromDate;
	SET @tDate = @toDate;
	
	IF (@fDate IS NULL)
		SELECT @fDate = CONVERT(DATETIME, '1900/01/01 00:00');
		
	IF (@tDate IS NULL)
		SELECT @tDate = CONVERT(DATETIME,'2100/01/01 00:00');

    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END
	
	IF @ERROR <> 0
		RETURN -1;

	SELECT OP.EXECUTEDAT, OP.AMOUNT, SVC.NAME AS SERVICENAME, OP.REASON FROM DBO.OPERATIONS AS OP, dbo.Services AS SVC
			WHERE type>=200 AND type<300 AND EXECUTEDAT BETWEEN @fDate AND @tDate AND SVC.id = OP.serviceid AND OP.userid = @USERID
			ORDER BY OP.executedat ASC
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getServicePassword]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	does searching of service by name for CRC checking

CREATE PROCEDURE [dbo].[sp_api_getServicePassword]
	-- service name
	@name varchar(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	-- check parameters
    IF @NAME IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END

	-- RETRIEVE DATA
	SELECT ID, PASSWORD FROM SERVICES WHERE NAME=@NAME
	
	if @@ROWCOUNT = 0
	begin
		select @error = dbo.sf_int_get_error_code('E_INVALID_SERVICE');
		return -1;
	end
	RETURN 0;	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getServiceSettings]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getServiceSettings]
	-- user name, cannot be null
	@user varchar(80),
	-- service name, cannot be null
	@serviceName varchar(80),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	SELECT @error = 0;

	-- check parameters	
	IF @USER IS NULL OR @serviceName IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- resolve service
	IF @ERROR = 0
    BEGIN
        SELECT @SERVICEID = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        IF @SERVICEID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @SERVICEID
    END

    IF @ERROR <> 0
		RETURN -1;
    

	SELECT PASSWORD, PROPERTIES FROM DBO.USERSERVICES
		WHERE USERID=@USERID AND SERVICEID = @SERVICEID AND ACTIVE=1;

	IF @@ROWCOUNT = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Cannot find service settings', @userid, @SERVICEID, @@ERROR;
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
	END

	if @ERROR<>0
		RETURN -1;

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getServicesList]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	Retrieves list of services by user id

CREATE PROCEDURE [dbo].[sp_api_getServicesList]
	-- user name, cannot be NULL
	@user varchar(80),
	--
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	DECLARE @USID INT;
    -- check parameters
	IF @USER IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
	-- check user for existing
	SELECT @USID = ID FROM USERS WHERE NAME=@user
	IF @USID IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
		RETURN -1;
	END

	-- retrieve full services list with subscription marks
	SELECT SC.ID AS SERVICEID, SC.NAME AS SERVICENAME, CASE WHEN US.ACTIVE IS NULL THEN 0 ELSE US.ACTIVE END AS SUBSCR  
		FROM SERVICES AS SC LEFT JOIN USERSERVICES AS US 
		ON US.USERID = @USID AND US.SERVICEID = SC.ID

	RETURN 0;
END
GO
/****** Object:  View [dbo].[vw_api_accountMap]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_api_accountMap]
AS
SELECT     NULL AS serviceId, dbo.Users.id AS userid, dbo.Accounts.name AS accName, dbo.Accounts.id AS accId, dbo.Accounts.id AS opId, CONVERT(bit, 0) 
                      AS cbtMode
FROM         dbo.Accounts INNER JOIN
                      dbo.Users ON dbo.Accounts.id = dbo.Users.accid
UNION ALL
SELECT     dbo.Services.id AS serviceId, dbo.UserServices.userid, Accounts_2.name AS accName, Accounts_2.id AS accId, Accounts_2.id AS opId, 
                      dbo.Services.cbtMode
FROM         dbo.Services INNER JOIN
                      dbo.UserServices ON dbo.Services.id = dbo.UserServices.serviceid INNER JOIN
                      dbo.Accounts AS Accounts_2 ON dbo.UserServices.accountid = Accounts_2.id
WHERE     (dbo.Services.independent = 1)
UNION ALL
SELECT     Services_1.id AS serviceId, UserServices_1.userid, Accounts_1.name AS accName, Accounts_1.id AS accId, Users_1.accid AS opId, 
                      Services_1.cbtMode
FROM         dbo.Services AS Services_1 INNER JOIN
                      dbo.UserServices AS UserServices_1 ON Services_1.id = UserServices_1.serviceid INNER JOIN
                      dbo.Accounts AS Accounts_1 ON UserServices_1.accountid = Accounts_1.id INNER JOIN
                      dbo.Users AS Users_1 ON UserServices_1.userid = Users_1.id
WHERE     (Services_1.independent = 0)
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4[30] 2[27] 3) )"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 3
   End
   Begin DiagramPane = 
      PaneHidden = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
      Begin ColumnWidths = 9
         Width = 284
         Width = 1725
         Width = 1440
         Width = 2205
         Width = 2100
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 5
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_api_accountMap'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_api_accountMap'
GO
/****** Object:  StoredProcedure [dbo].[sp_api_protocolRequest]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/18
-- Description:	Bans user on service

CREATE PROCEDURE [dbo].[sp_api_protocolRequest]
	-- service id
	@svcid INT = NULL,
	-- service name
	@serviceName varchar(80) = NULL,
	-- request content	
	@content TEXT = NULL,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	-- check parameters
    IF (@svcid IS NULL AND  @serviceName IS NULL)
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
	
	-- resolve service
	IF @ERROR = 0 AND @svcid IS NULL
    BEGIN
        SELECT @svcid = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        
        IF @svcid IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @svcid
    END
    
    
    IF @ERROR = 0
		EXEC dbo.sp_int_addProtocolRecord @typeid = 101, @serviceid = @svcid,  @parameters = @content, @error = @error OUTPUT
	
	IF @ERROR = 0
		RETURN 0;
		
	RETURN -1;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_unsubscribeUser]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/09
-- Description:	Does un-subscription of user for service
-- =============================================
CREATE PROCEDURE [dbo].[sp_api_unsubscribeUser]
	@userName VARCHAR(80),
	@serviceName VARCHAR(80),
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SET @error = 0;
	
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	-- check parameters	
	IF @userName IS NULL OR @serviceName IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @userName;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- resolve service
	IF @ERROR = 0
    BEGIN
        SELECT @SERVICEID = ID FROM SERVICES WHERE SERVICES.NAME = @serviceName;
        IF @SERVICEID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
        ELSE
            EXEC dbo.sp_int_trace 'Service detected', @SERVICEID
    END
    
    -- try to unsubscribe user
    IF @ERROR = 0
    BEGIN
		BEGIN TRANSACTION UNSUBSCIBE_SERVICE
		DECLARE @USID INT;
		DECLARE @USACTIVE BIT;

		SELECT @USID=ID, @USACTIVE=ACTIVE FROM USERSERVICES 
			WHERE USERID=@userid AND SERVICEID=@SERVICEID

		IF @USID IS NULL or @USACTIVE = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Service already unsubscriped',@USID ;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		END;

		IF @ERROR = 0
		BEGIN
			EXEC dbo.sp_int_trace 'Un-subscribe service',@USID ;
			UPDATE USERSERVICES SET active=0 WHERE ID = @USID
			IF @@ROWCOUNT = 0
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		END

		if @ERROR<>0
			ROLLBACK TRANSACTION UNSUBSCIBE_SERVICE;
		ELSE
			COMMIT TRANSACTION UNSUBSCIBE_SERVICE;
	END	
	
	-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	EXEC dbo.sp_log_unsubscribeUser @svcid = @SERVICEID, -- int
									@userid = @USERID, -- int
									@userName = @userName, -- varchar(80)
									@serviceName = @serviceName, -- varchar(80)
									@state = @ERROR, -- int
									@error = @errlog OUTPUT -- int
		
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================
	
	if @ERROR<>0
		RETURN -1;

	RETURN 0;		
END
GO
/****** Object:  UserDefinedFunction [dbo].[sf_get_config_value]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/03
-- Description:	Retrieves valuue of configuartion setting

CREATE FUNCTION [dbo].[sf_get_config_value] (@name varchar(80)) 
RETURNS sql_variant
AS
BEGIN
	DECLARE @result sql_variant;
	SELECT @result = ST.value from dbo.Settings as ST where ST.name = @name;
	return @result
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_create_temp]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Andrey V. Limorov
-- Create date: 2010/04/27
-- Update 1:    2010/05/04 (P.Yermalovich) Inserting new table for transactions
-- Update 2:    2010/05/10 (P.Yermalovich) 
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_payments_create_temp]
	-- session id
	@spid INT
AS
BEGIN
	
	SET NOCOUNT ON;
	BEGIN TRANSACTION T1
		-- creates the table to store data about groups
		IF OBJECT_ID('tempdb..##tmp_rptPaymentsGroups') is NULL
			BEGIN
				CREATE TABLE ##tmp_rptPaymentsGroups (spid INT, groupid INT, start DECIMAL(15,2), finish DECIMAL(15,2),);
				CREATE INDEX ##tmp_rptPaymentsGroups_idx_1 ON ##tmp_rptPaymentsGroups (spid);
				CREATE INDEX ##tmp_rptPaymentsGroups_idx_2 ON ##tmp_rptPaymentsGroups (spid,groupid);
				 
				EXEC dbo.sp_int_trace '##tmp_rptPaymentsGroups recreated', @spid 
			END	
		ELSE
			DELETE FROM ##tmp_rptPaymentsGroups WHERE spid = @spid;
			
		-- creates the table to store data about users	
		IF OBJECT_ID('tempdb..##tmp_rptPaymentsUsers') is NULL
			BEGIN
				CREATE TABLE ##tmp_rptPaymentsUsers (spid INT, groupid INT, userid INT,  periodid INT);
				CREATE INDEX ##tmp_rptPaymentsUsers_idx_1 ON ##tmp_rptPaymentsUsers (spid);
				CREATE INDEX ##tmp_rptPaymentsUsers_idx_2 ON ##tmp_rptPaymentsUsers (spid,groupid);
				 
				EXEC dbo.sp_int_trace '##tmp_rptPaymentsUsers recreated', @spid 
			END	
		ELSE
			DELETE FROM ##tmp_rptPaymentsUsers WHERE spid = @spid;
		
		-- creates the table to store chosen systems		
		IF OBJECT_ID('tempdb..##tmp_rptPaymentsSystems') is NULL		
			BEGIN
				CREATE TABLE ##tmp_rptPaymentsSystems (spid INT, systemid INT);
				CREATE INDEX ##tmp_rptPaymentsSystems_idx_1 ON ##tmp_rptPaymentsSystems (spid);
				CREATE INDEX ##tmp_rptPaymentsSystems_idx_2 ON ##tmp_rptPaymentsSystems (spid, systemid);
				EXEC dbo.sp_int_trace '##tmp_rptPaymentsSystems recreated', @spid 
			END	
		ELSE
			DELETE FROM ##tmp_rptPaymentsSystems WHERE spid = @spid;
	COMMIT TRANSACTION T1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses__buildAndGetGroups]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/25
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_expenses__buildAndGetGroups]
	-- session id
	@spid INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL,
	-- from total amount
	@fromTotalAmount DECIMAL(15,2),
	-- to total amount
	@toTotalAmount DECIMAL(15,2),
	-- from transaction count
	@fromTransactionCount INT,
	-- to transaction count
	@toTransactionCount INT,
	-- list of games (services)
	@serviceIdList VARCHAR(8000) = NULL,
	-- list of subjects 
	@subjectList VARCHAR(8000) = NULL,
	-- mask of user names
	@userMask VARCHAR(80) = NULL,
	-- list of groups
	@groupsList VARCHAR(8000) = NULL
AS
BEGIN

	IF @spid IS NULL
		SET @spid = @@SPID;

	-- FILL GROUPS
	-- -------------------------------------------------------------
	EXEC sp_rpt_expenses_fillGroups @spid, @groupsList;

	
	
	-- CHECK PARAMETERS	
	-- -------------------------------------------------------------
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
	
	-- check TotalAmount parameters
	IF(@fromTotalAmount IS NULL)
		SET @fromTotalAmount=0;
		
	IF(@toTotalAmount IS NULL)
		SET @toTotalAmount=9999999999999.99;
		
	-- check TransactionCount parameters
	IF(@fromTransactionCount IS NULL)
		SET @fromTransactionCount=0;
		
	IF(@toTransactionCount IS NULL)
		SET @toTransactionCount=10000000;
		
	-- check user mask
	IF (@userMask IS NULL)
		SET @userMask = '%'	
	
	
	
	-- FILL GAMES	
	-- -------------------------------------------------------------
	IF (@serviceIdList IS NOT NULL)
		INSERT INTO ##tmp_rptExpensesGames
			SELECT @spid, CAST(part AS INT)  AS serviceid FROM [sf_int_split](@serviceIdList,',')
	ELSE
		INSERT INTO ##tmp_rptExpensesGames
			SELECT @spid, id FROM dbo.Services
			
			
	-- fill subjects
	IF (@subjectList IS NOT NULL)
		INSERT INTO ##tmp_rptExpensesSubjects
			SELECT @spid, CAST(part AS NVARCHAR(80)) FROM [sf_int_split](@subjectList,'|')
	ELSE
		INSERT INTO ##tmp_rptExpensesSubjects
			SELECT DISTINCT @spid, CAST(reason AS NVARCHAR(80)) FROM dbo.Operations	
			WHERE	serviceid IS NOT NULL AND
					CAST(reason AS NVARCHAR(80)) IS NOT NULL AND
					type>=200 AND type<=300
						

	-- calculate the range of previous period
	DECLARE @fromDateOld DATETIME;
	SET @fromDateOld = @fromDate - (@toDate - @fromDate);	
	
	EXEC dbo.sp_int_trace 'Input parameters',@fromDate, @toDate, @fromTotalAmount,@userMask, @serviceIdList, @groupsList
	
	-- создаем временную таблицу для отфильтрованных юзеров
	DECLARE @filteredUsers AS TABLE
	(
		userid INT,
		totalAmount DECIMAL(15,2) 
	)
	-- заполняем ее			
	INSERT INTO @filteredUsers 
		-- User ID, Сумма трат по юзеру
		SELECT OP.userid , SUM(OP.amount) FROM Operations AS OP
		-- присоединение для поиска по маске
		INNER JOIN Users AS US ON OP.userid=US.id
		WHERE
			--фильтрация по дате
			OP.executedat BETWEEN @fromDate AND @toDate
			--по маске
			AND US.name LIKE @userMask
			--по играм
			AND OP.serviceid IN (SELECT serviceid FROM ##tmp_rptExpensesGames WHERE spid=@spid)
			AND CAST(OP.reason AS NVARCHAR(80)) IN (SELECT reason FROM ##tmp_rptExpensesSubjects WHERE spid=@spid)
		GROUP BY OP.userid
		--фильтрация по кол-ву транзакций и выплаченных денег
		HAVING
			SUM(OP.amount) BETWEEN @fromTotalAmount AND @toTotalAmount
			AND COUNT(OP.amount) BETWEEN @fromTransactionCount AND @toTransactionCount
	
	
    -- get current user groups
	INSERT INTO ##tmp_rptExpensesUsers
		
		SELECT @spid, EG.groupid, FU.userid, 1 FROM @filteredUsers AS FU
		INNER JOIN ##tmp_rptExpensesGroups AS EG ON EG.spid = @spid AND
		((EG.START IS NULL AND EG.finish IS NULL) OR
		  ((EG.finish IS NULL OR FU.totalAmount < EG.finish) AND 
		   (EG.start IS NULL OR FU.totalAmount >= EG.start)))
		
	-- заполняем эту же таблицу пользователями с прошлого периода
	DELETE FROM @filteredUsers
	
	INSERT INTO @filteredUsers 
	
		SELECT OP.userid , SUM(OP.amount) FROM Operations AS OP
		INNER JOIN Users AS US ON OP.userid=US.id
		WHERE
			OP.executedat BETWEEN @fromDateOld AND @fromDate
			AND US.name LIKE @userMask
			AND OP.serviceid IN (SELECT serviceid FROM ##tmp_rptExpensesGames)
			AND CAST(OP.reason AS NVARCHAR(80)) IN (SELECT reason FROM ##tmp_rptExpensesSubjects) 
		GROUP BY OP.userid
		HAVING
			SUM(OP.amount) BETWEEN @fromTotalAmount AND @toTotalAmount
			AND COUNT(OP.amount) BETWEEN @fromTransactionCount AND @toTransactionCount 
	
			
	INSERT INTO ##tmp_rptExpensesUsers
		SELECT @spid, EG.groupid, FU.userid, 0 AS periodid FROM @filteredUsers AS FU
		INNER JOIN ##tmp_rptExpensesGroups AS EG ON EG.spid = @spid AND
		((EG.START IS NULL AND EG.finish IS NULL) OR
		  ((EG.finish IS NULL OR FU.totalAmount < EG.finish) AND 
		   (EG.start IS NULL OR FU.totalAmount >= EG.start)))
	
	SET FMTONLY OFF;

	SELECT * FROM ##tmp_rptExpensesGroups WHERE spid = @spid;
	

END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_create_temp]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/05
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_expenses_create_temp]
	-- session id
	@spid INT
AS
BEGIN
	SET NOCOUNT ON;
	-- creates the table to store data about groups
	IF OBJECT_ID('tempdb..##tmp_rptExpensesGroups') is NULL
		BEGIN
			CREATE TABLE ##tmp_rptExpensesGroups (spid INT, groupid INT, start DECIMAL(15,2), finish DECIMAL(15,2));
			CREATE INDEX ##tmp_rptExpensesGroups_idx_1 ON ##tmp_rptExpensesGroups (spid);
			CREATE INDEX ##tmp_rptExpensesGroups_idx_2 ON ##tmp_rptExpensesGroups (spid,groupid);
			 
			EXEC dbo.sp_int_trace '##tmp_rptExpensesGroups recreated', @spid 
		END	
	ELSE
		DELETE FROM ##tmp_rptExpensesGroups WHERE spid = @spid;
		
		
	-- creates the table to store groups for previous period		
	IF OBJECT_ID('tempdb..##tmp_rptExpensesUsers') is NULL
		BEGIN
			CREATE TABLE ##tmp_rptExpensesUsers(spid INT, groupid INT,userid INT,  periodid INT);
			CREATE INDEX ##tmp_rptExpensesUsers_idx_1 ON ##tmp_rptExpensesUsers (spid);
			CREATE INDEX ##tmp_rptExpensesUsers_idx_2 ON ##tmp_rptExpensesUsers (spid,userid);
			EXEC dbo.sp_int_trace '##tmp_rptExpensesUsers recreated', @spid 
		END
	ELSE
		DELETE FROM ##tmp_rptExpensesUsers WHERE spid = @spid;	
	
	-- creates the table to store chosen games (services)		
	IF OBJECT_ID('tempdb..##tmp_rptExpensesGames') is NULL		
		BEGIN
			CREATE TABLE ##tmp_rptExpensesGames (spid INT, serviceid INT);
			CREATE INDEX ##tmp_rptExpensesGames_idx_1 ON ##tmp_rptExpensesGames (spid);
			CREATE INDEX ##tmp_rptExpensesGames_idx_2 ON ##tmp_rptExpensesGames (spid, serviceid);
			EXEC dbo.sp_int_trace '##tmp_rptExpensesGames recreated', @spid 
		END	
	ELSE
		DELETE FROM ##tmp_rptExpensesGames WHERE spid = @spid;
		
		
	-- creates the table to store chosen reasons (subjects)		
	IF OBJECT_ID('tempdb..##tmp_rptExpensesSubjects') is NULL		
		BEGIN
			CREATE TABLE ##tmp_rptExpensesSubjects (spid INT, reason NVARCHAR(80));
			CREATE INDEX ##tmp_rptExpensesSubjects_idx_1 ON ##tmp_rptExpensesSubjects (spid);
			CREATE INDEX ##tmp_rptExpensesSubjects_idx_2 ON ##tmp_rptExpensesSubjects (spid, reason);
			EXEC dbo.sp_int_trace '##tmp_rptExpensesSubjects recreated', @spid 
		END	
	ELSE
		DELETE FROM ##tmp_rptExpensesSubjects WHERE spid = @spid;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_getBalanceEx]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_getBalanceEx]
	-- user name
	@user varchar(80),
	-- service id
    @svcid    int,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	SET NOCOUNT ON;
	
	DECLARE @USERID INT;
	declare @partnerId int
    -- check parameters
	IF @USER IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END

	--check subscription, and auto-subscription
	if ( @ERROR = 0 )
	BEGIN
	declare @active bit
	SELECT @active = active FROM UserServices 
			WHERE userid = @USERID AND serviceid = @svcid;
		IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
		BEGIN
			declare @template xml
			SELECT @template = PARAMETERS FROM DBO.TEMPLATES WHERE isnull(partnerId, 0) = isnull(@partnerId, 0)
			if (@template.exist('/template/service[id=sql:variable("@svcid")]') = 1)
			BEGIN
				declare @errorInSubscribe int
				select @errorInSubscribe = 0
				EXEC dbo.sp_int_subscribeUser	@USERID = @userid, -- int
												@SERVICEID = @svcid, -- int
												@password = NULL, -- varbinary(80)
												@error =  @errorInSubscribe OUTPUT -- int
				if (@errorInSubscribe <> 0)
					select @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
			END
			else
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		END
	END

	IF @error <> 0
		RETURN -1;
	
	DECLARE @cbtpsid INT;
	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();

	--DECLARE @amount DECIMAL(15, 2);
	CREATE TABLE #tmp (
		userid int,
		amount decimal(15, 2),
		psid int
	);

	IF @svcid IS NULL
		--SELECT @amount=SUM(amount) FROM dbo.VW_UserBalance WHERE id = @userid AND systemid <> @cbtpsid		
		
		INSERT INTO #tmp 
		SELECT id, amount, systemid FROM dbo.VW_UserBalance WHERE id = @userid AND systemid <> @cbtpsid;
		
		--SELECT * SUM(amount) FROM dbo.VW_UserBalance WHERE id = 68798		
	ELSE
	BEGIN
		DECLARE @opid INT;
		DECLARE @cbtmode BIT;

		SELECT @opid=opid, @cbtmode=cbtMode FROM dbo.vw_api_accountMap WHERE userId = @USERID AND serviceId = @svcid
		
		IF @opid IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');
		
		IF @error <> 0
			RETURN -1;

		if 	@cbtmode = 0
			INSERT INTO #tmp			
			SELECT 
				a.userid,
				sa.amount,
				sa.systemid
			FROM
				dbo.SubAccounts sa
				INNER JOIN PaymentSystems ps ON sa.systemid = ps.id
				INNER JOIN Accounts a ON a.id = sa.accid
			WHERE 
				sa.accid = @opid AND sa.systemid <> @cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)
		
			--SELECT @amount = SUM(sa.amount) 
			--FROM dbo.SubAccounts sa
			--INNER JOIN PaymentSystems ps
			--ON sa.systemid = ps.id
			--WHERE sa.accid = @opid AND sa.systemid <> @cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)
		else
			INSERT INTO #tmp
			SELECT
				a.userid,
				sa.amount,
				sa.systemid
			FROM 
				dbo.Accounts a
				INNER JOIN dbo.SubAccounts sa ON sa.accid = a.id
			WHERE
				a.id = @opid AND sa.systemid = @cbtpsid			
		
			--SELECT @amount = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @opid AND systemid = @cbtpsid
	END	

	--IF @amount IS NULL
	--	SET @amount=0;
	
	--declare @reservedAmount decimal
	--select @reservedAmount = sum(amount) from WriteOffReserve where accountId = @opid and cbt = @cbtmode

	--temp logging
--	DECLARE @content VARCHAR(8000);
--	SELECT @content = 
--		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END
--		
--	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 550, 
--			@serviceid=@svcid, @userid = @USERID, @amount = @amount, 
--			@parameters = @content, @error = @error OUTPUT
	--/temp logging	


	--SELECT ( @amount - isnull(@reservedAmount, 0) ) AS AMOUNT;
	SELECT 
		userid, SUM(amount) as amount, psid 
	FROM 
		#tmp
	GROUP BY 
		userid, psid;
		
	DROP TABLE #tmp;
	
	/* need for xsd
	select 
		CAST(123 as int) as userid,
		CAST(1 as decimal) as amount,
		CAST(321 as int) as psid*/
	

	RETURN 0;
END

/*DECLARE @error int;
EXEC dbo.sp_api_getBalanceEx 'hudbrog', 14, @error OUTPUT
SELECT @error

EXEC dbo.sp_api_getBalance 'hudbrog', 14, @error OUTPUT
*/
GO
/****** Object:  View [dbo].[vw_gui_Templates]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_gui_Templates]
AS
SELECT     id, name, mask
FROM         dbo.Templates
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "Templates"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 197
               Right = 189
            End
            DisplayFlags = 280
            TopColumn = 0
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_Templates'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'vw_gui_Templates'
GO
/****** Object:  UserDefinedFunction [dbo].[sf_int_resolve_template]    Script Date: 09/08/2013 16:06:14 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/03
-- Description:	Does resolving of template by referal code

-- =============================================
CREATE FUNCTION [dbo].[sf_int_resolve_template] (@referal varchar(4000))
RETURNS int
AS
BEGIN
	DECLARE @RESULTVAR INT;
	SET @RESULTVAR = NULL;
	-- try to resolve template by code
	IF NOT @REFERAL IS NULL
	BEGIN
		SELECT TOP 1 @RESULTVAR=T.ID FROM DBO.TEMPLATES AS T
			WHERE @REFERAL LIKE T.MASK
	END
	-- try to find default template
	IF (@RESULTVAR IS NULL)
		SELECT @RESULTVAR=T.ID FROM DBO.TEMPLATES AS T WHERE T.MASK IS NULL

	RETURN @RESULTVAR

END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_getTemplates]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/03/10
-- Description:	getting template
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_getTemplates] 
	-- parameters for the stored procedure

AS
BEGIN

	SELECT id, name, description, mask, priority, parameters FROM DBO.TEMPLATES ORDER BY priority ASC

END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_increaseTemplatePriority]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/03/10
-- Description:	increasing template priority
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_increaseTemplatePriority] 
	-- parameters for the stored procedure
	@id			int,
	@admid		int,
	@error int OUTPUT

AS
BEGIN
	SELECT @error = 0;
	declare @realPriority	int;
	declare @prevPriority	int;	
	declare @tempPriority	int;
	declare @templateId		int;

	if @id is NULL
	begin
		return -1;
	end

	SET @tempPriority = -999999;

	SELECT @realPriority=priority 
	FROM DBO.TEMPLATES 
	WHERE ID = @id

	IF @realPriority IS NULL
		RETURN -1;

	SELECT TOP 1 @prevPriority = priority, @templateId = id 
	FROM DBO.TEMPLATES 
	WHERE (priority > @realPriority)
	ORDER BY priority ASC
		
	IF @prevPriority IS NULL
		RETURN -1;	

	BEGIN TRANSACTION T_INCREASE_TEMPLATE_PRIORITY
		
	UPDATE DBO.TEMPLATES
	SET priority=@tempPriority
	WHERE id=@templateId

	IF( @@ERROR <> 0 )
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');

	IF @ERROR =0
	BEGIN
		UPDATE DBO.TEMPLATES
		SET PRIORITY=@PREVPRIORITY
		WHERE ID=@ID

		IF( @@ERROR <> 0 )
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	END

	IF @error =0
	BEGIN
		UPDATE DBO.TEMPLATES
		SET PRIORITY=@REALPRIORITY
		WHERE ID=@TEMPLATEID

		IF( @@ERROR <> 0 )
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	END

	IF( @error <> 0 )
	BEGIN
		ROLLBACK TRANSACTION T_INCREASE_TEMPLATE_PRIORITY
		RETURN -1;
    END

	COMMIT TRANSACTION T_INCREASE_TEMPLATE_PRIORITY
	RETURN 1;

END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_autoSubscribe]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_autoSubscribe]
	@svcid INT,
	@userid INT,
	@partnerId INT,
	@error int OUTPUT
AS
BEGIN
	
	declare @template xml
	SELECT @template = PARAMETERS FROM DBO.TEMPLATES WHERE isnull(partnerId, 0) = isnull(@PARTNERID, 0)
	declare @isInTemplate bit
	select @isInTemplate = @template.exist('/template/service[id=sql:variable("@svcid")]') 		
	if (@isInTemplate = 1)
	BEGIN
		EXEC dbo.sp_int_subscribeUser	@USERID = @userid, -- int
										@SERVICEID = @svcid, -- int
										@password = NULL, -- varbinary(80)
										@error =  @error OUTPUT -- int
		if ( @error <> 0 )
			select @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	END
	else
		SELECT @error = DBO.SF_INT_GET_ERROR_CODE('E_UNSUBSCRIBED');

	IF @error <> 0
		RETURN -1
	
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_apply_template]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/02
-- Description:	Applyes template on newly created user
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_apply_template]
	@userid int,
	@TEMPLATEID int,
	@error int OUTPUT
AS
BEGIN
	SET @error = 0;
	DECLARE @OPERID INT;

    IF @USERID IS NULL OR @TEMPLATEID IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END

	DECLARE @BODY XML;
	DECLARE @AMOUNT DECIMAL(15,2);
	DECLARE @SUBACCID int;

	SELECT @BODY =  PARAMETERS FROM DBO.TEMPLATES WHERE ID = @TEMPLATEID
	IF @BODY IS NULL
	BEGIN
		EXEC dbo.sp_int_trace 'Template body is NULL';
		RETURN -1;	
	END
		
	SELECT @AMOUNT = @BODY.value('/template[1]/amount[1]','DECIMAL(15,2)')
	IF @AMOUNT IS NULL or @AMOUNT<0
	BEGIN
		EXEC dbo.sp_int_trace 'Amount has invalid value';
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');	
		RETURN -1;	
	END
	
	IF @ERROR=0 AND @AMOUNT>0
	BEGIN
	-- try to apply start money
		EXEC dbo.sp_int_trace 'Try to do start replenish by', @AMOUNT
		DECLARE @accid int;
		DECLARE @bonusesps int
		SELECT @accid = accid from USERS where id = @userid;
		SELECT @bonusesps = dbo.sf_int_get_bonuses_ps();
		EXEC dbo.sp_int_replenish @userid, @accid, @bonusesps, @AMOUNT, 101, 'Start money', @OPERID OUTPUT, @error OUTPUT
	END

	IF @ERROR=0
	BEGIN
		DECLARE @svid int, @svset varchar(8000)
		
		DECLARE S1 CURSOR FOR SELECT T1.rows.value('./id[1]','int') as id, T1.rows.value('./settings[1]','varchar(8000)') as settings
			FROM @BODY.nodes('/template/service') T1(rows)
		
		OPEN S1
		FETCH NEXT FROM S1 INTO @svid, @svset
		-- for every service in template
		
		WHILE @@FETCH_STATUS = 0 AND @ERROR = 0
		BEGIN
			if @svid IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
			ELSE
			BEGIN	
				EXEC dbo.sp_int_trace 'Try to auto-subscribe', @userid, @svid
				EXEC dbo.sp_int_subscribeUser @userid, @svid, NULL, @ERROR OUTPUT  
				FETCH NEXT FROM S1 INTO @svid, @svset 
			END
		END

		CLOSE S1
		DEALLOCATE S1
	END

	IF @ERROR<>0
		RETURN -1;
	ELSE
		RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_gui_decreaseTemplatePriority]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/03/10
-- Description:	decreasing template priority
-- =============================================
CREATE PROCEDURE [dbo].[sp_gui_decreaseTemplatePriority] 
	-- parameters for the stored procedure
	@id			int,
	@admid		int,
	@error		int OUTPUT

AS
BEGIN
	SELECT @error = 0;
	declare @realPriority	int;
	declare @prevPriority	int;	
	declare @tempPriority	int;
	declare @templateId		int;

	if @id is NULL
	begin
		return -1;
	end

	SET @tempPriority = -999999;

	SELECT @realPriority=priority 
	FROM DBO.TEMPLATES 
	WHERE ID = @id

	IF @realPriority IS NULL
		RETURN -1;

	SELECT TOP 1 @prevPriority = priority, @templateId = id 
	FROM DBO.TEMPLATES 
	WHERE (priority < @realPriority)
	ORDER BY priority DESC

	EXEC dbo.sp_int_trace 'Previous priority = ', @prevPriority	
	EXEC dbo.sp_int_trace 'Previous template id = ', @templateId	
	
	IF @prevPriority IS NULL
		RETURN -1;	

	BEGIN TRANSACTION T_DECREASE_TEMPLATE_PRIORITY
		
	UPDATE DBO.TEMPLATES
		SET priority=@tempPriority
		WHERE id=@templateId

	IF( @@ERROR <> 0 )
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');

	IF @ERROR =0
	BEGIN
		UPDATE DBO.TEMPLATES
		SET PRIORITY=@PREVPRIORITY
		WHERE ID=@ID

		IF( @@ERROR <> 0 )
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	END

	IF @error =0
	BEGIN
		UPDATE DBO.TEMPLATES
		SET PRIORITY=@REALPRIORITY
		WHERE ID=@TEMPLATEID

		IF( @@ERROR <> 0 )
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
	END

	IF( @error <> 0 )
	BEGIN
		ROLLBACK TRANSACTION T_DECREASE_TEMPLATE_PRIORITY
		RETURN -1;
    END

	COMMIT TRANSACTION T_DECREASE_TEMPLATE_PRIORITY
	RETURN 1;

END
GO
/****** Object:  View [dbo].[vw_gui_KWAccBalance]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create view [dbo].[vw_gui_KWAccBalance]
as
select UserServices.userid as UserID, SUM(case when SubAccounts.systemid <> 1 and SubAccounts.systemid <> 2 then amount else null end) as RealBalance,
	SUM(CASE WHEN systemid = 1 THEN amount ELSE NULL END) AS BonusMoney
from 
Accounts inner join SubAccounts on Accounts.id = SubAccounts.accid
inner join UserServices on SubAccounts.accid = UserServices.accountid
where UserServices.serviceid = 14 --kw ёхЁтшё id
group by UserServices.userid
GO
/****** Object:  View [dbo].[vw_gui_CommonAccBalance]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create view [dbo].[vw_gui_CommonAccBalance]
as
select Users.id as UserID, SUM(case when SubAccounts.systemid <> 1 and SubAccounts.systemid <> 2 then amount else null end) as RealBalance,
	SUM(CASE WHEN systemid = 1 THEN amount ELSE NULL END) AS BonusMoney
from 
Accounts inner join SubAccounts on Accounts.id = SubAccounts.accid
inner join Users on Accounts.id = Users.accid
group by Users.id
GO
/****** Object:  View [dbo].[vw_UserBalance]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_UserBalance] WITH SCHEMABINDING
AS
SELECT     dbo.Accounts.userid AS id, SUM(dbo.SubAccounts.amount) AS amount, dbo.SubAccounts.systemid, COUNT_BIG(*) AS cnt
FROM         dbo.Accounts INNER JOIN
                      dbo.SubAccounts ON dbo.Accounts.id = dbo.SubAccounts.accid
GROUP BY dbo.Accounts.userid, dbo.SubAccounts.systemid
GO
/****** Object:  View [dbo].[View_1]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[View_1]
AS
SELECT     p.userid, p.serviceid
FROM         dbo.Protocols AS p INNER JOIN
                          (SELECT     userid
                            FROM          dbo.Protocols
                            WHERE      (occurredat >= '2010-01-01 00:00:00')
                            GROUP BY userid
                            HAVING      (COUNT(DISTINCT serviceid) >= 2)) AS u ON p.userid = u.userid
WHERE     (p.id =
                          (SELECT     MIN(id) AS Expr1
                            FROM          dbo.Protocols AS ipr
                            WHERE      (serviceid IN (1, 3, 5, 7, 8, 14, 16, 17, 18, 19, 24)) AND (typeid = 501) AND (userid = p.userid)))
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = 0
         Left = 0
      End
      Begin Tables = 
         Begin Table = "p"
            Begin Extent = 
               Top = 0
               Left = 477
               Bottom = 240
               Right = 833
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "u"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 80
               Right = 198
            End
            DisplayFlags = 280
            TopColumn = 0
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
      Begin ColumnWidths = 9
         Width = 284
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
         Width = 1500
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 11
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'View_1'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'View_1'
GO
/****** Object:  StoredProcedure [dbo].[sp_int_send_user_fraud_mail]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Bans user on service

CREATE PROCEDURE [dbo].[sp_int_send_user_fraud_mail]
	-- 	service id, cannot be null
	@svcid INT,
	-- user id, cannot be null
	@userid INT,
	-- fraud parameter	
	@parameter VARCHAR(80),
	-- fraud level	
	@level INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @error = 0;
		
	DECLARE @descr VARCHAR(200);

	-- check parameters	
	IF @svcid IS NULL OR @userid IS NULL OR @parameter IS NULL OR @level IS NULL OR NOT @level BETWEEN 1 AND 2
	BEGIN
		EXEC dbo.sp_int_trace 'Invalid parameters for sp_int_send_user_fraud_mail', @svcid, @svcid, @userid, @parameter
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
   
    -- resolve user
    IF @ERROR = 0
    BEGIN
		SELECT @descr = description FROM dbo.FraudSettings WHERE code = @parameter;
        IF @descr IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
    END

    
	IF @ERROR = 0
    BEGIN
		DECLARE @mailType INT;
		IF @level = 1
			SET @mailType = 101;
		ELSE			
			SET @mailType = 102;
		EXEC dbo.sp_int_send_mail @type = @mailType, -- int
			    @svcid = @svcid, -- int
			    @userid = @userid, -- int
			    @adminMail = 0, -- varchar(100)
			    @param1 = @descr, -- nvarchar(200)
			    @error = @error OUTPUT -- int
			    
    END

	if @ERROR<>0
	BEGIN
		EXEC dbo.sp_int_trace 'Unable to send fraud notify message with', @svcid, @userid, @descr
		RETURN -1;
	END		

	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_legacy_getBalance]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/05/24
-- Description:	Retrieves current user legacy balance
-- =============================================
CREATE PROCEDURE [dbo].[sp_legacy_getBalance] 
	-- user name
	@user varchar(80),
	-- ip (id code) of caller service
	@remoteIp VARCHAR(15),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	SET NOCOUNT ON;
	
	DECLARE @SVCID INT;

	IF @error = 0
	BEGIN
		SELECT @SVCID= serviceid  FROM dbo.LegacyServices WHERE ip = @remoteIp;
		IF @SVCID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
		ELSE
            EXEC dbo.sp_int_trace 'Service detected', @remoteIp, @SVCID
	END
	
	IF @error = 0
		EXEC dbo.sp_api_getBalance @user, @SVCID, @error OUTPUT 

	IF @error = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_legacy_accountLogin]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/16
-- Description:	does user legacy authorization

CREATE PROCEDURE [dbo].[sp_legacy_accountLogin]
	-- user name
	@user varchar(80),
	-- password
	@password varbinary(80),
	-- ip (id code) of caller service
	@remoteIp VARCHAR(15), 
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	SET NOCOUNT ON;
	
	DECLARE @SVCID INT;

	IF @error = 0
	BEGIN
		SELECT @SVCID= serviceid  FROM dbo.LegacyServices, dbo.Services WHERE ip = @remoteIp;
		IF @SVCID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_SERVICE');
		ELSE
            EXEC dbo.sp_int_trace 'Service detected', @remoteIp, @SVCID
	END
	
	-- normal authorization
	IF @error = 0
		EXEC dbo.sp_api_authorizeUser @SVCID, @user, @password, @error OUTPUT 

	IF @error = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_legacy_protocolRequest]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/18
-- Description:	Does logging of legacy request content

CREATE PROCEDURE [dbo].[sp_legacy_protocolRequest]
	-- service id
	@svcid INT = NULL,
	-- user name
	@user varchar(80) = NULL,
	-- request content	
	@content TEXT = NULL,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	DECLARE @userid INT;
	-- check parameters
    IF (@svcid IS NULL AND  @user IS NULL)
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
	
	-- resolve service
	IF @ERROR = 0 AND NOT @user IS NULL
    BEGIN
        SELECT @userid = ID FROM dbo.Users WHERE Users.NAME = @user;
        
        IF @userid IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @userid
    END
    
    
    IF @ERROR = 0
		EXEC dbo.sp_int_addProtocolRecord @typeid = 102, @serviceid = @svcid, @userid=@userid, @parameters = @content, @error = @error OUTPUT
	
	IF @ERROR = 0
		RETURN 0;
		
	RETURN -1;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_totalBanWithTemporary]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_totalBanWithTemporary]
	@user varchar(80),
	@empid int,
	@hours int = null,
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	SELECT @error = 0;

	-- check parameters	
	IF @USER IS NULL or @empid IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- ban
	IF @ERROR = 0
    BEGIN
        if (@hours is null)--means final
		BEGIN
			update Users 
				set finalBan = 1 where id = @USERID
		END
		else --means temp
		BEGIN
			update Users 
				set tempBan = DATEADD(hour, @hours, getdate()) where id = @USERID
		END
    END

	-- log request ================================================================================
	IF @ERROR = 0
	BEGIN
		DECLARE @content VARCHAR(8000);
		SELECT @content = 
			':@name=' + @user +
			':@hours='  + CASE WHEN @hours IS NULL THEN 'null' ELSE CONVERT(VARCHAR(10), @hours) END;
			
		EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 506, @userid = @userid, @empid = @empid, @parameters = @content, @result=@error, @error = @error OUTPUT
		
		IF @@ERROR <> 0
		BEGIN
			EXEC dbo.sp_int_trace 'Error on add log record', @ERROR
			RETURN -1;
		END
	END
	if (@ERROR <> 0)
		RETURN -1;
	-- end log request ============================================================================
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_unTotalBan]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_unTotalBan]
	@user varchar(80),
	@empid int,
	@removeTempBan bit = null,
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @USERID INT;
	DECLARE @SERVICEID INT;
	
	SELECT @error = 0;

	-- check parameters	
	IF @USER IS NULL or @empid IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
    
    -- resolve user
    IF @ERROR = 0
    BEGIN
        SELECT @USERID = ID FROM USERS WHERE USERS.NAME = @USER;
        IF @USERID IS NULL
            SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
        ELSE
            EXEC dbo.sp_int_trace 'User detected', @USERID
    END
    
    -- unban
	IF @ERROR = 0
    BEGIN
        if (@removeTempBan = 1) --remove temp
		BEGIN
			update Users 
				set tempBan = null where id = @USERID
		END
		else --remove final
		BEGIN
			update Users 
				set finalBan = null where id = @USERID
		END
    END

	-- log request ================================================================================
	IF @ERROR = 0
	BEGIN
		DECLARE @content VARCHAR(8000);
		SELECT @content = 
			':@name=' + @user +
			':@removeTempBan='  + CASE WHEN @removeTempBan = 1  THEN '1' ELSE 'not 1' END;
			
		EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 507, @userid = @userid, @empid = @empid, @parameters = @content, @result=@error, @error = @error OUTPUT
		
		IF @@ERROR <> 0
		BEGIN
			EXEC dbo.sp_int_trace 'Error on add log record', @ERROR
			RETURN -1;
		END
	END
	if (@ERROR <> 0)
		RETURN -1;
	-- end log request ============================================================================
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_replenish]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does logging of replenish operations

CREATE PROCEDURE [dbo].[sp_log_replenish]

	-- caller service id
	@svcid	int,
	-- id of user
	@userid INT,
	-- amount
	@amount DECIMAL(15,2),
	-- id of account	
	@accid INT,
	-- id of payment system
	@systemid INT,
	-- id of opertaion
	@operationid INT,

	
	-- user name
	@user varchar(80),
	-- account name. can be null. in this case acount of user-service subscription will be used
	@account varchar(50),
	-- payment system name
	@paymentsystem varchar(80),
	
	-- reason of operation
	@reason text,
	

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END + 
		':@account='  + CASE WHEN @account IS NULL THEN 'null' ELSE @account END +
		':@paymentsystem=' + CASE WHEN @paymentsystem IS NULL THEN 'null' ELSE @paymentsystem END +
		':@reason='  +CONVERT(VARCHAR(2000),CASE WHEN @reason IS NULL THEN 'null' ELSE @reason END);
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 504, 
			@serviceid=@svcid, @userid = @userid, @systemid = @systemid, @operationid = @operationid, @amount = @amount, 
			@parameters = @content, @result = @state, @error = @error OUTPUT

	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_setServiceSettings]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/30
-- Description:	does logging of set service settings operation

CREATE PROCEDURE [dbo].[sp_log_setServiceSettings]
	-- service id
	@svcid INT,
	-- user id
	@userid INT,

	-- user name, cannot be null
	@user varchar(80),
	-- service name, cannot be null
	@serviceName varchar(80),
	-- new specific password or NULL
	@password varbinary(80) = NULL,
	-- new specific settings or NULL
	@properties XML,
	
	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END +
		':@serviceName='  + CASE WHEN @serviceName IS NULL THEN 'null' ELSE @serviceName END +
		':@password='  +   CONVERT(VARCHAR(160), CASE WHEN @password IS NULL THEN 'null' ELSE @password END) +
		':@properties='  +  CONVERT(VARCHAR(6000), CASE WHEN @properties IS NULL THEN 'null' ELSE @properties END);
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 512, @serviceid = @svcid, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_setUserPassword]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Julia Khvasko
-- Create date: 2010/06/09
-- Description:	does logging of set user password operation
-- =============================================
CREATE PROCEDURE [dbo].[sp_log_setUserPassword]
	-- user id
	@userid INT,
	-- user name, cannot be null
	@user varchar(80),
	-- password
	@password varbinary(80),

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END + 
		':@password=' + CASE WHEN @password IS NULL THEN 'null' ELSE CONVERT(varchar(80),@password) END;

	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 515, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_setUserProfile]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/30
-- Description:	does logging of set user profile operation

CREATE PROCEDURE [dbo].[sp_log_setUserProfile]
	-- service id
	@svcid INT,
	-- user id
	@userid INT,

	-- user name, cannot be null
	@user varchar(80),
	-- display name of user
	@displayName varchar(200),
	-- email address
	@email VARCHAR(80),
	-- agreement 
	@agreement bit,

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END +
		':@displayName='  + CASE WHEN @displayName IS NULL THEN 'null' ELSE @displayName END +
		':@email='  + CASE WHEN @email IS NULL THEN 'null' ELSE @email END +
		':@agreement='  +   CONVERT(VARCHAR(20), CASE WHEN @agreement IS NULL THEN 'null' ELSE @agreement END); 

		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 509, @serviceid = @svcid, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_subscribeUser]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/30
-- Description:	does logging of subscribe user operation

CREATE PROCEDURE [dbo].[sp_log_subscribeUser]
	-- service id
	@svcid INT,
	-- user id
	@userid INT,

	-- user name
	@userName VARCHAR(80),
	-- service name
	@serviceName VARCHAR(80),
	-- special password
	@password varbinary(80),

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@userName='  + CASE WHEN @userName IS NULL THEN 'null' ELSE @userName END +
		':@serviceName='  + CASE WHEN @serviceName IS NULL THEN 'null' ELSE @serviceName END +
		':@password='  +   CONVERT(VARCHAR(160), CASE WHEN @password IS NULL THEN 'null' ELSE @password END); 
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 510, @serviceid = @svcid, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_transfer]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does logging of transfer operations

CREATE PROCEDURE [dbo].[sp_log_transfer]

	-- caller service id
	@svcid	int,
	-- id of user
	@userid INT,
	-- amount
	@amount DECIMAL(15,2),
	-- id of opertaion
	@operationid INT,


	-- source id of account	
	@srcaccid INT,
	-- dest id of account	
	@dstaccid INT,	
	-- user name
	@srcUser varchar(80),
	-- source account name
	@srcaccount varchar(50),
	-- dest user name
	@dstUser varchar(80),
	-- dest account name
	@dstaccount varchar(50),
	-- reason of operation
	@reason text,
	

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@srcUser='  + CASE WHEN @srcUser IS NULL THEN 'null' ELSE @srcUser END + 
		':@srcaccount='  + CASE WHEN @srcaccount IS NULL THEN 'null' ELSE @srcaccount END +
		':@srcaccid='  +  CONVERT(VARCHAR(20),CASE WHEN @srcaccid IS NULL THEN -1 ELSE @srcaccid END) + 
		':@dstUser='  + CASE WHEN @dstUser IS NULL THEN 'null' ELSE @dstUser END + 
		':@dstaccount='  + CASE WHEN @dstaccount IS NULL THEN 'null' ELSE @dstaccount END +
		':@dstaccid='  +  CONVERT(VARCHAR(20),CASE WHEN @dstaccid IS NULL THEN -1 ELSE @dstaccid END) + 
		':@reason='  +CONVERT(VARCHAR(2000),CASE WHEN @reason IS NULL THEN 'null' ELSE @reason END);
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 505, 
			@serviceid = @svcid, @userid = @userid, @operationid = @operationid, @amount = @amount, 
			@parameters = @content, @result = @state, @error = @error OUTPUT

	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_unbanUser]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	does logging of bam user operation

CREATE PROCEDURE [dbo].[sp_log_unbanUser]
	-- service id
	@svcid INT,
	-- user id
	@userid INT,
	
	-- user name
	@name varchar(80),
	-- service name
	@serviceName varchar(80),
	-- user name
	@reason text,

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@name='  + CASE WHEN @name IS NULL THEN 'null' ELSE @name END + 
		':@serviceName='  + CASE WHEN @serviceName IS NULL THEN 'null' ELSE @serviceName END +
		':@reason='  +  CONVERT(VARCHAR(4000), CASE WHEN @reason IS NULL THEN 'null' ELSE @reason END);
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 507, @serviceid=@svcid, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_unsubscribeUser]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/30
-- Description:	does logging of unsubscribe user operation

CREATE PROCEDURE [dbo].[sp_log_unsubscribeUser]
	-- service id
	@svcid INT,
	-- user id
	@userid INT,

	-- user name
	@userName VARCHAR(80),
	-- service name
	@serviceName VARCHAR(80),

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@userName='  + CASE WHEN @userName IS NULL THEN 'null' ELSE @userName END +
		':@serviceName='  + CASE WHEN @serviceName IS NULL THEN 'null' ELSE @serviceName END; 
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 510, @serviceid = @svcid, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_writeOff]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/19
-- Description:	does user authorization

CREATE PROCEDURE [dbo].[sp_log_writeOff]

	-- caller service id
	@svcid	INT,
	-- resolved user id
	@userid INT,
	-- ammount
	@amount DECIMAL(15,2),
	-- created operation id
	@operationid INT,
	
	-- user name
	@user varchar(80),
	-- account name
	@account varchar(50),
	-- real account id
	@accid INT,
	-- reason of operation
	@reason text,

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END + 
		':@account='  + CASE WHEN @account IS NULL THEN 'null' ELSE @account END +
		':@reason='  +CONVERT(VARCHAR(2000),CASE WHEN @reason IS NULL THEN 'null' ELSE @reason END);
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 503, @serviceid=@svcid, @userid = @userid, @operationid = @operationid, 
		@amount = @amount, @parameters = @content, @result = @state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_authorizeUser]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/19
-- Description:	does user authorization

CREATE PROCEDURE [dbo].[sp_log_authorizeUser]
	-- service id
	@svcid INT,
	-- user id
	@userid INT,
	-- user name
	@user VARCHAR(80),
	-- password
	@password varbinary(80),
	-- error cod of operation	
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000)
	SELECT @content = 
		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END + 
		':@password=' + CASE WHEN @password IS NULL THEN 'null' ELSE CONVERT(varchar(80),@password) END;
	
	SELECT @content;
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 501, @serviceid = @svcid, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	

	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_adminWriteOff]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/04/05
-- Description:	does logging of admin write-off operations

CREATE PROCEDURE [dbo].[sp_log_adminWriteOff]

	-- caller employer id
	@empid	INT,
	-- resolved user id
	@userid INT,
	-- payment system id
	@systemid INT,
	-- ammount
	@amount DECIMAL(15,2),
	-- created operation id
	@operationid INT,
	-- real account id
	@accid INT,

	-- reason of operation
	@reason text,

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	EXEC dbo.sp_int_trace 'mess', @state, @accid
	
	DECLARE @content VARCHAR(MAX);
	SELECT @content = ':@accid='  + CASE WHEN @accid IS NULL THEN 'null' ELSE CONVERT(VARCHAR(MAX), @accid) END +
	':@reason='  + CASE WHEN @reason IS NULL THEN 'null' ELSE CONVERT(VARCHAR(MAX),@reason) END;

	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 514, @empid = @empid, @userid = @userid, @operationid = @operationid, 
		@systemid = @systemid, @amount = @amount, @parameters = @content, @result = @state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_promoActivation]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/19
-- Description:	does user authorization

CREATE PROCEDURE [dbo].[sp_log_promoActivation]

	-- caller service id
	@svcid	int,
	-- user id
	@userid INT,
	-- account id
	@accid INT,

	
	-- user name
	@user varchar(80),
	-- account name. can be null. in this case acount of user-service subscription will be used
	@account varchar(50),
	-- promocode
	@promo  varchar(80),
	-- error code
	@state int ,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@user='  + CASE WHEN @user IS NULL THEN 'null' ELSE @user END + 
		':@account='  + CASE WHEN @account IS NULL THEN 'null' ELSE @account END +
		':@accid='  +  CONVERT(VARCHAR(20),CASE WHEN @accid IS NULL THEN -1 ELSE @accid END) + 
		':@promo='  + CASE WHEN @promo IS NULL THEN 'null' ELSE @promo END;
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 508, @serviceid=@svcid, @userid = @userid, 
		@parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_generatePromocodes]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/19
-- Description:	does logging of promocodes generation

CREATE PROCEDURE [dbo].[sp_log_generatePromocodes]
	-- employer id
	@empid INT,
	-- full amount of operation
	@fullamount DECIMAL(15,2),
	-- operation id
	@operationid INT,
	-- amount
	@amount DECIMAL(15,2),
	-- count of promocodes
	@count INT,
	-- reason
	@reason TEXT,
	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@count='  +  CONVERT(VARCHAR(20),CASE WHEN @count IS NULL THEN -1 ELSE @count END) +
		':@amount='  +  CONVERT(VARCHAR(20),CASE WHEN @amount IS NULL THEN -1 ELSE @amount END) +
		':@reason='  + CONVERT(VARCHAR(MAX),CASE WHEN @reason IS NULL THEN 'null' ELSE @reason END);
		
	EXEC dbo.sp_int_addProtocolRecord @typeid = 513, @empid = @empid, @operationid = @operationid, --@systemid = dbo.sf_int_get_bonuses_ps(),
		@amount = @fullamount, @result = @state, @parameters = @content, @error = @error OUTPUT 


	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_createUser]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/19
-- Description:	does user authorization

CREATE PROCEDURE [dbo].[sp_log_createUser]
	-- user name
	@name varchar(80),
	-- e-mail
	@email varchar(80),
	-- password
	@password varbinary(80),
	-- referal code, can be NULL
	@referal varchar(80),

	-- id of user
	@userid INT,
	-- resolved partner ID
	@partnerid INT,
	-- resolved template ID
	@templateid INT,
	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@name='  + CASE WHEN @name IS NULL THEN 'null' ELSE @name END + 
		':@email='  + CASE WHEN @email IS NULL THEN 'null' ELSE @email END +
		':@password=' + CASE WHEN @password IS NULL THEN 'null' ELSE CONVERT(varchar(80),@password) END +
		':@referal='  + CASE WHEN @referal IS NULL THEN 'null' ELSE @referal END +
		':@partnerid='  +  CASE WHEN @partnerid IS NULL THEN 'null' ELSE CONVERT(VARCHAR(20),@partnerid) END +
		':@templateid='  + CASE WHEN @templateid IS NULL THEN 'null' ELSE CONVERT(VARCHAR(20),@templateid) END;
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 502, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_log_banUser]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	does logging of bam user operation

CREATE PROCEDURE [dbo].[sp_log_banUser]
	-- service id
	@svcid INT,
	-- user id
	@userid INT,
	
	-- user name
	@name varchar(80),
	-- service name
	@serviceName varchar(80),
	-- user name
	@reason text,

	-- state of request
	@state INT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @content VARCHAR(8000);
	SELECT @content = 
		':@name='  + CASE WHEN @name IS NULL THEN 'null' ELSE @name END + 
		':@serviceName='  + CASE WHEN @serviceName IS NULL THEN 'null' ELSE @serviceName END +
		':@reason='  +  CASE WHEN @reason IS NULL THEN 'null' ELSE CONVERT(VARCHAR(MAX), @reason) END;
		
	EXEC  dbo.[sp_int_addProtocolRecord] @typeid = 506, @serviceid = @svcid, @userid = @userid, @parameters = @content, @result=@state, @error = @error OUTPUT
	
	IF @error = 0
		RETURN 0;
	
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_writeOff_acc_sub]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/10
-- Description:	Writes-off from sub account
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_writeOff_acc_sub]
    -- id of main operation
    @OPERID INT,
	-- sub account id
	@SUBACCID INT,
	-- ammount of operation
	@AMOUNT decimal(15,2),
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;

    IF @OPERID IS NULL OR @SUBACCID IS NULL OR @AMOUNT IS NULL OR @AMOUNT<0
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END
    
    BEGIN TRANSACTION T_SUB_WOFF

    -- CHANGE BALANCE =============================    
    -- CONSTRAINT ERROR CATCH========================
 BEGIN TRY
    UPDATE DBO.SUBACCOUNTS
        SET AMOUNT = AMOUNT - @AMOUNT 
        WHERE ID = @SUBACCID 
    IF @@ROWCOUNT = 0
        SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
end try
BEGIN CATCH
    if  ERROR_NUMBER() = 547 and ERROR_SEVERITY() = 16
begin 
SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
end
END CATCH;
        
    IF @ERROR = 0
    BEGIN
    -- INSERT TRANSACTION =========================
        INSERT INTO dbo.Transactions (operationid, subaccid, amount)
			VALUES (@OPERID, @SUBACCID, @AMOUNT)
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');        
    END
	
	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_SUB_WOFF
		RETURN 0;
	END
	ROLLBACK TRANSACTION T_SUB_WOFF
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_post_checkFraudLogin]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does fraud checking of login operations
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_post_checkFraudLogin]
	@svcid INT,
	@userid INT,
	@state INT,
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;

	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @switch=0
   	BEGIN
   		SELECT @error = @state;
    	RETURN 0;
	END    	
    		
	DECLARE @invpasswd INT; 
	SELECT @invpasswd = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_PASSWORD');

	DECLARE @ret INT;
	DECLARE @value INT;
	SET @ret = 0;
	
	EXEC dbo.sp_int_trace '[sp_int_post_checkFraudLogin]',@state,@invpasswd,@error
	-- check login tries ===============================================================
	IF @state = @invpasswd AND @error = 0
	BEGIN
		-- select count of unsucessfull login after last sucessful login(501) or unban(507)
		SELECT @value = COUNT(*) FROM dbo.Protocols WHERE typeid = 501 AND userid = @userid AND result = @invpasswd AND ID >
			(SELECT TOP 1 ID FROM dbo.Protocols WHERE (typeid = 501 OR typeid = 507) AND userid = @userid AND result = 0 ORDER BY ID DESC)
		
		IF (@value IS NULL)
			SELECT @value = 1;

		SELECT @value = @value + 1;	

		EXEC dbo.sp_int_trace 'Check LOGIN.MAX.TRIES variable',@value
		
		IF (NOT @value IS NULL)
		BEGIN
			EXEC @ret = dbo.sp_int_checkFraudValue 'LOGIN.MAX.TRIES', @value, @error = @ERROR OUTPUT
			IF @error = 0 AND @ret > 0	
			BEGIN		
				EXEC [dbo].[sp_int_send_user_fraud_mail]	@svcid = @svcid,
															@userid = @userid,
															@parameter = 'LOGIN.MAX.TRIES',
															@level = @ret,
															@error = @error OUTPUT		
			END																
		END															
	END
	
	
	-- ban user on red level
	IF @error = 0 AND @ret = 2
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
		
		DECLARE @errlog INT;
		SELECT @errlog = 0;
		
		EXEC dbo.sp_int_banUser @serviceid = @svcid, -- int
		    @userid = @userid, -- int
		    @reason = 'Auto ban on fraud checking of login', -- text
		    @error = @errlog OUTPUT
		IF (@errlog<>0)    
		BEGIN
			EXEC dbo.sp_int_trace 'Unable to do ban of user', @svcid, @userid, @errlog;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED'); 
		END			
	END	
	ELSE
		SELECT @ERROR = @state;
		
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_post_checkFraudPromo]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does post fraud checking of promo activation
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_post_checkFraudPromo]
	-- id of service
	@svcid INT,
	-- id of user
	@userid INT,
	
	@state INT,
	-- error code
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @switch=0
   	BEGIN
   		SELECT @error = @state;
    	RETURN 0;
	END  
    		
	DECLARE @value DECIMAL(15,2);

	-- check input parameters
	IF @svcid IS NULL OR @userid IS NULL 
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END;
	

	DECLARE	@ret INT;
	SELECT @ret = 0;
	DECLARE	@ret_op INT;

	DECLARE @paramName VARCHAR(80);
	DECLARE @detectedName VARCHAR(80);	
	
	DECLARE @badpromo INT;
	SELECT @badpromo = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_PROMO');
	
	-- check for count of unsuccessful activations ======================================
	IF @state = @badpromo AND @error = 0  AND @ret < 2
	BEGIN
		SET @paramName = 'PROMO.MAX.TRIES';	

		SELECT @value = COUNT(*) FROM dbo.Protocols WHERE typeid = 508 AND userid = @userid AND result = @badpromo AND ID >
			( SELECT TOP 1 ID FROM dbo.Protocols WHERE (typeid = 508 OR typeid = 507) AND userid = @userid AND result = 0 ORDER BY ID DESC )
		
		IF (@value IS NULL)
			SELECT @value = 1;

		SELECT @value = @value + 1;
				
		EXEC dbo.sp_int_trace 'Check variable', @paramName, @value
		
		IF (NOT @value IS NULL)
		BEGIN

			EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName , @value, @error = @ERROR OUTPUT
			IF @error=0 AND @ret_op > @ret 
			BEGIN
				SET @ret = @ret_op;
				SET @detectedName = @paramName; 
			END	
		END	
	END

	IF @error = 0 AND @ret > 0
	BEGIN
	
		-- send mail to user, if ban ==========================================================
		IF @detectedName = 'PROMO.MAX.TRIES' AND @ret = 2
		BEGIN
			DECLARE @errlog INT;
			EXEC dbo.sp_int_banUser @serviceid = @svcid, -- int
										@userid = @userid, -- int
										@reason = 'Auto ban on promo activation', -- text
										@error = @errlog OUTPUT
			IF (@errlog<>0)    
			BEGIN
				EXEC dbo.sp_int_trace 'Unable to do ban of user', @svcid, @userid, @errlog;
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED'); 
			END	
			
			IF @error=0
				EXEC [dbo].[sp_int_send_user_fraud_mail] @svcid = @svcid,
														 @userid = @userid,
														 @parameter = @detectedName,
														 @level = @ret,
														 @error = @error OUTPUT					
		END
		
		-- send mail to admin, if non zero level detected =======================================
		IF @error=0
			EXEC [dbo].[sp_int_send_admin_fraud_mail]	 @svcid = @svcid,
														 @userid = @userid,
														 @parameter = @detectedName,
														 @level = @ret,
														 @error = @error OUTPUT				
	
	END				
		
	IF @error=0	
	BEGIN		
		IF @ret = 2
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
		ELSE	
			SELECT @ERROR = @state;
	END			

	EXEC dbo.sp_int_trace 'Result error', @ERROR;
	
	RETURN 0;
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_pre_checkFraudLogin]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does fraud checking of login operations
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_pre_checkFraudLogin]
	@svcid INT,
	@userid INT,
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @switch=0
    	RETURN 0;
    		
	IF @svcid IS NULL OR @userid IS NULL 
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END;

	DECLARE	@ret INT;
	SELECT @ret = 0;
	DECLARE	@ret_op INT;
	
	DECLARE @value INT;
/*
	-- check login tries per hour ======================================================	
	IF @error = 0 AND @ret<>2
	BEGIN
		DECLARE @invpasswd INT; 
		SELECT @invpasswd = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_PASSWORD');
		-- select count of unsucessfull login after last sucessful login(501) or unban(507)
		SELECT @value = COUNT(*) FROM dbo.Protocols WHERE typeid = 501 AND userid = @userid AND result = @invpasswd AND ID >
			(SELECT TOP 1 ID FROM dbo.Protocols WHERE (typeid = 501 OR typeid = 507) AND userid = @userid AND result = 0 ORDER BY ID DESC)
			
		EXEC dbo.sp_int_trace 'Check LOGIN.MAX.TRIES variable',@value
		
		IF (NOT @value IS NULL)
		BEGIN
			EXEC @ret_op = dbo.sp_int_checkFraudValue 'LOGIN.MAX.TRIES', @value, @error = @ERROR OUTPUT
			IF @error=0 AND @ret_op > @ret
			BEGIN
				SET @ret = @ret_op;
				EXEC [dbo].[sp_int_send_user_fraud_mail]	@svcid = @svcid,
															@userid = @userid,
															@parameter = 'LOGIN.MAX.TRIES',
															@level = @ret_op,
															@error = @error OUTPUT
			END				
		END	
	END*/
	
	-- check login tries per hour ======================================================	
	IF @error = 0 AND @ret<>2
	BEGIN
		SELECT @value = COUNT(*) FROM dbo.Protocols WHERE typeid = 501 AND userid = @userid AND occurredat >= DATEADD(hour,-1,GETDATE());

		EXEC dbo.sp_int_trace 'Check LOGIN.MAX.PER.HOUR variable',@value
		
		IF (NOT @value IS NULL)
		BEGIN
			EXEC @ret_op = dbo.sp_int_checkFraudValue 'LOGIN.MAX.PER.HOUR', @value, @error = @ERROR OUTPUT
			IF @error=0 AND @ret_op > @ret
			BEGIN
				SET @ret = @ret_op;
				EXEC [dbo].[sp_int_send_user_fraud_mail]	@svcid = @svcid,
															@userid = @userid,
															@parameter = 'LOGIN.MAX.TRIES',
															@level = @ret_op,
															@error = @error OUTPUT
			END					
		END	
	END
	
	-- ban user on red level
	IF @error = 0 AND @ret = 2
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
		
		DECLARE @errlog INT;
		SELECT @errlog = 0;
		
		EXEC dbo.sp_int_banUser @serviceid = @svcid, -- int
		    @userid = @userid, -- int
		    @reason = 'Auto ban on fraud checking of login', -- text
		    @error = @errlog OUTPUT
		IF (@errlog<>0)    
		BEGIN
			EXEC dbo.sp_int_trace 'Unable to do ban of user', @svcid, @userid, @errlog;
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED'); 
		END			
	END		    

END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_pre_checkFraudPromo]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does fraud checking of promo activation
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_pre_checkFraudPromo]
	-- id of service
	@svcid INT,
	-- id of user
	@userid INT,
	-- error code
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @switch INT;
	
	DECLARE @paramName VARCHAR(80);
	DECLARE @detectedName VARCHAR(80);
	
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @switch=0
    	RETURN 0;
    		
	DECLARE @value DECIMAL(15,2);
	
	-- check input parameters
	IF @svcid IS NULL OR @userid IS NULL 
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END;

	DECLARE	@ret INT;
	SELECT @ret = 0;
	DECLARE	@ret_op INT;
	
	-- check for count of unsuccessful activations ======================================
	/*IF @error = 0 AND @ret<2
	BEGIN
		SET @paramName = 'PROMO.MAX.TRIES';	
		
		DECLARE @badpromo INT;
		SELECT @badpromo = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_PROMO');
		SELECT @value = COUNT(*) FROM dbo.Protocols WHERE typeid = 508 AND userid = @userid AND result = @badpromo AND ID >
			( SELECT TOP 1 ID FROM dbo.Protocols WHERE (typeid = 508 OR typeid = 507) AND userid = @userid AND result = 0 ORDER BY ID DESC )
		
		EXEC dbo.sp_int_trace 'Check variable', @paramName, @value
		
		IF (NOT @value IS NULL)
		BEGIN

			EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName , @value, @error = @ERROR OUTPUT
			IF @error=0 AND @ret_op > @ret 
			BEGIN
				SET @ret = @ret_op;
				SET @detectedName = @paramName; 
			END	
		END	
	END
	*/
	
	-- check count of promo activations per week ========================================
	IF @error = 0 AND @ret<2
	BEGIN
		SET @paramName = 'PROMO.MAX.PER.WEEK';	
		SELECT @value = COUNT(*) FROM dbo.Protocols 
			WHERE typeid = 508 AND userid = @userid AND result = 0 AND occurredat >= DATEADD(day,-7,GETDATE());
			
		EXEC dbo.sp_int_trace 'Check variable',@paramName, @value
		
		IF (NOT @value IS NULL)
		BEGIN
			EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @value, @error = @ERROR OUTPUT
			IF @error = 0 AND @ret_op > @ret 
			BEGIN
				SET @ret = @ret_op;
				SET @detectedName = @paramName; 
			END	
		END	
	END
	
	-- check for amount of bonuses ======================================
	IF @error = 0 AND @ret<2
	BEGIN
		SET @paramName = 'BONUSES.MAX.RATE';
		DECLARE @rate DECIMAL(38,2)
		SET @rate = dbo.sf_int_getBonusesRate();

		EXEC dbo.sp_int_trace 'Check variable',@paramName, @rate
		
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @rate, @error = @ERROR OUTPUT
		IF @error = 0 AND @ret_op > @ret 
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END	
	
	-- pre checking sends messages only on level 2
	IF @error = 0 AND @ret >0 
	BEGIN
	
		-- send mail to user, if ban ==========================================================
	/*	IF @detectedName = 'PROMO.MAX.TRIES'
		BEGIN
			DECLARE @errlog INT;
			EXEC dbo.sp_int_banUser @serviceid = @svcid, -- int
										@userid = @userid, -- int
										@reason = 'Auto ban on promo activation', -- text
										@error = @errlog OUTPUT
			IF (@errlog<>0)    
			BEGIN
				EXEC dbo.sp_int_trace 'Unable to do ban of user', @svcid, @userid, @errlog;
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED'); 
			END	
			
			IF @error=0
				EXEC [dbo].[sp_int_send_user_fraud_mail] @svcid = @svcid,
														 @userid = @userid,
														 @parameter = @detectedName,
														 @level = @ret,
														 @error = @error OUTPUT					
		END*/
		
		-- send mail to admin, if non zero level detected =======================================
		IF @error=0
			EXEC [dbo].[sp_int_send_admin_fraud_mail]	 @svcid = @svcid,
														 @userid = @userid,
														 @parameter = @detectedName,
														 @level = @ret,
														 @error = @error OUTPUT				
		
		IF @error=0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
	END				
					
	IF @error=0
		RETURN 0;
		
	RETURN -1;	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_checkFraudWriteOff]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/22
-- Description:	Does fraud checking of write-off operations
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_checkFraudWriteOff]
	-- amount of operation
	@amount DECIMAL(15,2),
	-- id of service
	@svcid INT,
	-- id of users
	@userid INT,
	-- error code
	@error INT OUTPUT
AS
BEGIN
	SELECT @error = 0;
	
	DECLARE @switch INT;
	SET @switch =  CONVERT(INT,dbo.sf_get_config_value('FRAUD.CHECK.ENABLED'));
   	if @switch=0
    	RETURN 0;
	
	DECLARE @value DECIMAL(15,2);
	DECLARE @paramName VARCHAR(80);
	DECLARE @detectedName VARCHAR(80);
	
	DECLARE	@ret INT;
	SELECT @ret = 0;
	DECLARE	@ret_op INT;
	
	-- check input parameters
	IF @svcid IS NULL OR @userid IS NULL OR @amount IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END;
	
	-- check for max operation amount ==============================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'WRITEOFF.MAX.AMOUNT'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amount, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	-- check count and amount per day ==================================
	DECLARE @amtpd DECIMAL(15,2);
	DECLARE @cntpd DECIMAL(15,2);

	IF @error = 0 AND @ret<>2
	BEGIN
		SELECT @amtpd = SUM(amount), @cntpd = COUNT(*)
			FROM dbo.Operations WHERE userid=@userid AND type=102 AND executedat>= DATEADD(day,-1,GETDATE());
		set @amtpd = case when @amtpd IS NULL THEN 0 ELSE @amtpd END + @amount;
		set @cntpd = @cntpd+1;
		EXEC dbo.sp_int_trace 'Amount and count of payments of user per day', @amtpd, @cntpd
	END

	---- check amount per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'WRITEOFF.MAX.AMOUNT.TRANSACTIONS.PER.DAY';
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amtpd, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	---- check count per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'WRITEOFF.MAX.COUNT.TRANSACTIONS.PER.DAY'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @cntpd, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- check count and amount per weak =================================
	DECLARE @amtpw DECIMAL(15,2);
	DECLARE @cntpw DECIMAL(15,2);

	IF @error = 0 AND @ret<>2
	BEGIN
		SELECT @amtpw = SUM(amount), @cntpw = COUNT(*) 
			FROM dbo.Operations WHERE userid=@userid AND type=102 AND executedat>= DATEADD(day,-7,GETDATE());
		set @amtpw = case when @amtpw IS NULL THEN 0 ELSE @amtpw END + @amount;
		set @cntpw = @cntpw+1;
		EXEC dbo.sp_int_trace 'Amount and count of payments of user per weak', @amtpw, @cntpw
	END

	---- check amount per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'WRITEOFF.MAX.AMOUNT.TRANSACTIONS.PER.WEEK';
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @amtpw, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END
	
	---- check count per day ==================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'WRITEOFF.MAX.COUNT.TRANSACTIONS.PER.WEEK'
		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @cntpw, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- check for amount of bonuses ======================================
	IF @error = 0 AND @ret<>2
	BEGIN
		SET @paramName = 'BONUSES.MAX.RATE';
		DECLARE @rate DECIMAL(15,2);
		SET @rate = dbo.sf_int_getBonusesRate();

		EXEC @ret_op = dbo.sp_int_checkFraudValue @paramName, @rate, @error = @ERROR OUTPUT
		IF @error=0 AND @ret_op > @ret
		BEGIN
			SET @ret = @ret_op;
			SET @detectedName = @paramName; 
		END	
	END

	-- send mail to admin, if non zero level detected =======================================
	IF @error=0 AND @ret >0
		EXEC [dbo].[sp_int_send_admin_fraud_mail]	 @svcid = @svcid,
													 @userid = @userid,
													 @parameter = @detectedName,
													 @level = @ret,
													 @error = @error OUTPUT	
		
	IF @error = 0 AND @ret = 2
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_ACCESS');
	
	IF @error=0
		RETURN 0;
		
	RETURN -1;	
END
GO
/****** Object:  View [dbo].[vw_gui_WrongUsersCommon]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create view [dbo].[vw_gui_WrongUsersCommon]
as
select nu.username, zm.[money] as oldMoney, zm.Bonus as oldBonus, v.RealBalance as newMoney, v.BonusMoney as newBonus, u.id as userid, u.accid as comAccId
--select sum(v.RealBalance)
from nivalusers nu
left join zzmoney zm
on nu.username = zm.username
left join Users u
on nu.username = u.[name]
left join vw_gui_CommonAccBalance v
on u.id = v.UserID
where (isnull(zm.money, 0) <> isnull(v.RealBalance, 0)) or (isnull(zm.Bonus, 0) <> isnull(v.BonusMoney, 0))
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_fillGroups]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/06
-- Description:	Retrieves base groups list for Expenses.rdl

CREATE PROCEDURE [dbo].[sp_rpt_expenses_fillGroups]
	@spid INT,
	@groupsList VARCHAR(MAX)
AS
BEGIN

	EXEC dbo.sp_rpt_expenses_create_temp @spid;

	DECLARE @gps TABLE(pos INT, part varchar(80));
	INSERT INTO @gps
		EXEC dbo.sp_int_split @groupsList,',';
	
	DELETE FROM ##tmp_rptExpensesGroups
		WHERE spid=@spid
	
	INSERT INTO ##tmp_rptExpensesGroups (spid, groupid, start)
		SELECT @spid, pos, CAST(part AS DECIMAL(15,2)) FROM @gps;


	IF @@ROWCOUNT<>0
	BEGIN
		UPDATE ##tmp_rptExpensesGroups
			SET finish=(
				SELECT start FROM ##tmp_rptExpensesGroups AS A 
				WHERE A.spid = B.spid 
					AND A.spid = @spid 
					AND A.groupId = B.groupId+1)
		FROM ##tmp_rptExpensesGroups AS B
	END
		
	--SELECT * FROM 	##tmp_rptExpensesGroups 
	--WHERE spid=@spid
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_fillGroups]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Andrey V. Limorov
-- Create date: 2010/04/27
-- Update 1: 2010/05/10 (P.Yermalovich)
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_payments_fillGroups]
	@spid INT,
	@groupsList VARCHAR(MAX)
AS
BEGIN
	EXEC dbo.sp_rpt_payments_create_temp @spid;
	
	INSERT INTO ##tmp_rptPaymentsGroups (spid, groupid, start)
		SELECT @spid, pos, CAST(part AS DECIMAL(15,2)) FROM dbo.sf_int_split(@groupsList,',');
	
	IF @@ROWCOUNT<>0
	BEGIN
		UPDATE ##tmp_rptPaymentsGroups
			SET finish=(
				SELECT start FROM ##tmp_rptPaymentsGroups AS A 
				WHERE A.spid = B.spid 
					AND A.spid = @spid 
					AND A.groupId = B.groupId+1)
		FROM ##tmp_rptPaymentsGroups AS B
	END
END
GO
/****** Object:  View [dbo].[vw_gui_Balances]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_gui_Balances]
AS
SELECT     id AS UserID, SUM(CASE WHEN systemid <> 2 AND systemid <> 1 THEN amount ELSE NULL END) AS RealBalance, 
                      SUM(CASE WHEN systemid = 1 THEN amount ELSE NULL END) AS BonusMoney, SUM(CASE WHEN systemid <> 2 THEN amount ELSE NULL END) 
                      AS Total
FROM         dbo.VW_UserBalance AS UB
GROUP BY id
GO
/****** Object:  StoredProcedure [dbo].[sp_legacy_transfer]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:        Limorov Andrey
-- Create date: 2010/03/17
-- Description:    Does money transfer legacy way
-- =============================================
CREATE PROCEDURE [dbo].[sp_legacy_transfer]
    -- caller service id
    @svcid    int,
    -- source user name
    @srcuser varchar(80),
    -- dest user name
    @destuser varchar(80),
    -- amount
    @amount decimal(15,2),
    -- reason of operation
    @reason text,
    -- error code
    @error int OUTPUT
AS
BEGIN
    SELECT  @ERROR = 0;
   
    IF  @svcid IS NULL OR @srcuser IS NULL OR @destuser IS NULL OR @amount IS NULL OR @amount<0
    BEGIN
        SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
    END 
    
    IF @ERROR = 0
        EXEC [dbo].[sp_api_transfer]  @SVCID, @SRCUSER, NULL, @destuser, NULL, @AMOUNT, @REASON, @ERROR OUTPUT;
    
    IF @ERROR = 0
    BEGIN
		RETURN 0;
	END

	RETURN -1;
END
GO
/****** Object:  View [dbo].[vw_gui_Users]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[vw_gui_Users]
AS
SELECT     us.id, us.name AS Username, pf.email, CASE WHEN dbo.vw_gui_Balances.Total IS NULL THEN 0 ELSE dbo.vw_gui_Balances.Total END AS Total, 
                      CASE WHEN dbo.vw_gui_Balances.RealBalance IS NULL THEN 0 ELSE dbo.vw_gui_Balances.RealBalance END AS RealBalance, 
                      CASE WHEN dbo.vw_gui_Balances.BonusMoney IS NULL THEN 0 ELSE dbo.vw_gui_Balances.BonusMoney END AS BonusMoney, 
                      dbo.PartnerPrograms.name AS PartnerProgram
FROM         dbo.Users AS us INNER JOIN
                      dbo.Profiles AS pf ON us.id = pf.userid LEFT OUTER JOIN
                      dbo.vw_gui_Balances ON pf.userid = dbo.vw_gui_Balances.UserID LEFT OUTER JOIN
                      dbo.PartnerPrograms ON us.partnerid = dbo.PartnerPrograms.id
GO
/****** Object:  StoredProcedure [dbo].[sp_int_writeOffWithBalance]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_writeOffWithBalance]
	@SVCID	INT,
	@USERID INT,
	@ACCID INT,
	@AMOUNT decimal(15,2),
	@TYPE INT,
	@REASON text,
	@cbt bit,
	@remainAmount decimal(15, 2) OUTPUT,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @cbtpsid INT; 
	DECLARE @balance decimal(15,2); 

	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();
	
	IF  @USERID IS NULL OR @ACCID IS NULL OR @AMOUNT IS NULL OR @AMOUNT<=0
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END 
	-- check for fraud
	IF @error = 0
	BEGIN
		EXEC dbo.sp_int_checkFraudWriteOff @amount = @AMOUNT, -- decimal
		    @svcid = @SVCID, -- int
		    @userid = @USERID, -- int
		    @error = @error OUTPUT -- int
	END
	
	BEGIN TRANSACTION T_WRITEOFF

	if 	@cbt = 0
		SELECT @balance = SUM(sa.amount) 
		FROM dbo.SubAccounts sa
		inner join PaymentSystems ps
		on sa.systemid = ps.id
		WHERE sa.accid = @ACCID AND sa.systemid <> @cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)
	else
		SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid = @cbtpsid


	EXEC dbo.sp_int_trace 'Current balance', @balance

	IF @ERROR = 0
	BEGIN
		--учитываем резерв если имеется
		declare @reservedAmount decimal
		select @reservedAmount = sum(amount) from WriteOffReserve where accountId = @ACCID and cbt = @cbt and finishTime > GETDATE()

		if (@balance IS NULL or (@balance - isnull(@reservedAmount, 0)) < @AMOUNT)
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
	END
    
    IF @ERROR = 0
	BEGIN
    
        EXEC dbo.sp_int_trace 'Try to create new operation', @balance
    
		-- INSERT  NEW OPERATION ===========================
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, SRCACCID, SERVICEID, REASON)
			VALUES (@AMOUNT, @USERID, GETDATE(), @TYPE, @ACCID, @SVCID, @REASON)
		
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END

	IF @ERROR = 0
	BEGIN
		DECLARE @AMTWK decimal(15,2);
		SET @AMTWK = @AMOUNT;
		DECLARE @SID INT, @SAMMOUNT decimal(15,2), @SYSTEMID INT;


		WHILE( @AMTWK > 0 AND @ERROR=0)
		BEGIN
            
			SELECT TOP 1 @SID = SC.ID, @SAMMOUNT = SC.AMOUNT, @SYSTEMID = SC.SYSTEMID from dbo.SubAccounts AS SC, dbo.PaymentSystems as PS	
				WHERE SC.AMOUNT > 0 AND SC.ACCID = @ACCID AND SC.SYSTEMID = PS.ID AND 
					 ((@cbt=0 AND SYSTEMID<>@cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)) OR (@cbt<>0 AND SYSTEMID=@cbtpsid))
				ORDER BY PS.priority ASC
            
                        
           	IF (@SID IS NULL)
            	SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
            
            IF @error=0
            BEGIN
                DECLARE @ToWriteOff decimal(15,2);
                IF @AMTWK < @SAMMOUNT
                    SELECT @ToWriteOff = @AMTWK;
                ELSE
                    SELECT @ToWriteOff = @SAMMOUNT;                     
                
                EXEC dbo.sp_int_trace 'Try to write off: sub account/amount/systemid', @SID, @ToWriteOff, @SYSTEMID 

            	EXEC dbo.sp_int_writeOff_acc_sub @OPERID, @SID, @ToWriteOff, @error OUTPUT;
				
				--add record for royalty calculation
				INSERT WriteOffsPaymentSystem(operationId, paymentSystemId, amount)
					VALUES (@OPERID, @SYSTEMID, @ToWriteOff)
               
                IF @ERROR = 0
                BEGIN
                    SELECT @AMTWK = @AMTWK - @ToWriteOff;
                    EXEC dbo.sp_int_trace 'Still to write off', @AMTWK  
                END
            END         			
		END
	END
	--get remained balance
	IF @ERROR = 0
	BEGIN
		if 	@cbt = 0
			SELECT @balance = SUM(sa.amount) 
			FROM dbo.SubAccounts sa
			inner join PaymentSystems ps
			on sa.systemid = ps.id
			WHERE sa.accid = @ACCID AND sa.systemid <> @cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)
		else
			SELECT @remainAmount = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid = @cbtpsid
	END
	select @remainAmount = @remainAmount - @reservedAmount
	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_WRITEOFF
		RETURN 0;
	END
	
	ROLLBACK TRANSACTION T_WRITEOFF 
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_writeOff]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_writeOff]
	@SVCID	INT,
	@USERID INT,
	@ACCID INT,
	@AMOUNT decimal(15,2),
	@TYPE INT,
	@REASON text,
	@cbt bit,
	@OPERID INT OUTPUT,
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @cbtpsid INT; 
	DECLARE @balance decimal(15,2); 

	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();
	
	IF  @USERID IS NULL OR @ACCID IS NULL OR @AMOUNT IS NULL OR @AMOUNT<=0
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END 
	-- check for fraud
	IF @error = 0
	BEGIN
		EXEC dbo.sp_int_checkFraudWriteOff @amount = @AMOUNT, -- decimal
		    @svcid = @SVCID, -- int
		    @userid = @USERID, -- int
		    @error = @error OUTPUT -- int
	END
	
	BEGIN TRANSACTION T_WRITEOFF
	
	if 	@cbt = 0
			SELECT @balance = SUM(sa.amount) 
			FROM dbo.SubAccounts sa
			inner join PaymentSystems ps
			on sa.systemid = ps.id
			WHERE sa.accid = @ACCID AND sa.systemid <> @cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)
		else
			SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid = @cbtpsid

	EXEC dbo.sp_int_trace 'Current balance', @balance

	IF @ERROR = 0
	BEGIN
		-- delete obsolete reserves
		delete from WriteOffReserve where accountId = @ACCID and cbt = @cbt and finishTime <= GETDATE();
	
		--учитываем резерв если имеется
		declare @reservedAmount decimal
		select @reservedAmount = sum(amount) from WriteOffReserve where accountId = @ACCID and cbt = @cbt and finishTime > GETDATE()

		if (@balance IS NULL or (@balance - isnull(@reservedAmount, 0)) < @AMOUNT)
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
	END
    
    IF @ERROR = 0
	BEGIN
    
        EXEC dbo.sp_int_trace 'Try to create new operation', @balance
    
		-- INSERT  NEW OPERATION ===========================
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, SRCACCID, SERVICEID, REASON)
			VALUES (@AMOUNT, @USERID, GETDATE(), @TYPE, @ACCID, @SVCID, @REASON)
		
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END

	IF @ERROR = 0
	BEGIN
		DECLARE @AMTWK decimal(15,2);
		SET @AMTWK = @AMOUNT;
		DECLARE @SID INT, @SAMMOUNT decimal(15,2), @SYSTEMID INT;


		WHILE( @AMTWK > 0 AND @ERROR=0)
		BEGIN
            
			SELECT TOP 1 @SID = SC.ID, @SAMMOUNT = SC.AMOUNT, @SYSTEMID = SC.SYSTEMID from dbo.SubAccounts AS SC, dbo.PaymentSystems as PS	
				WHERE SC.AMOUNT > 0 AND SC.ACCID = @ACCID AND SC.SYSTEMID = PS.ID AND 
					 ((@cbt=0 AND SYSTEMID<>@cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)) OR (@cbt<>0 AND SYSTEMID=@cbtpsid))
				ORDER BY PS.priority ASC
            
                        
           	IF (@SID IS NULL)
            	SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
            
            IF @error=0
            BEGIN
                DECLARE @ToWriteOff decimal(15,2);
                IF @AMTWK < @SAMMOUNT
                    SELECT @ToWriteOff = @AMTWK;
                ELSE
                    SELECT @ToWriteOff = @SAMMOUNT;                     
                
                EXEC dbo.sp_int_trace 'Try to write off: sub account/amount/systemid', @SID, @ToWriteOff, @SYSTEMID 

            	EXEC dbo.sp_int_writeOff_acc_sub @OPERID, @SID, @ToWriteOff, @error OUTPUT;
				
				--add record for royalty calculation
				INSERT WriteOffsPaymentSystem(operationId, paymentSystemId, amount)
					VALUES (@OPERID, @SYSTEMID, @ToWriteOff)
               
                IF @ERROR = 0
                BEGIN
                    SELECT @AMTWK = @AMTWK - @ToWriteOff;
                    EXEC dbo.sp_int_trace 'Still to write off', @AMTWK  
                END
            END         			
		END
	END


	IF @ERROR = 0
	BEGIN
		IF (@@TRANCOUNT > 0) COMMIT TRANSACTION T_WRITEOFF
		RETURN 0;
	END
	
	IF (@@TRANCOUNT > 0) ROLLBACK TRANSACTION T_WRITEOFF 
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_removeAmountWithReal]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_int_removeAmountWithReal]
	@SVCID	INT,
	@USERID INT,
	@ACCID INT,
	@AMOUNT decimal(15,2),
	@TYPE INT,
	@REASON text,
	@cbt bit,
	@OPERID INT OUTPUT,
	@realAmount decimal(15,2) OUTPUT,
	@error int OUTPUT
AS
BEGIN
SELECT @ERROR = 0;
	DECLARE @cbtpsid INT; 
	DECLARE @balance decimal(15,2); 

	SELECT @cbtpsid = dbo.sf_int_get_cbt_ps();
	
	IF  @USERID IS NULL OR @ACCID IS NULL OR @AMOUNT IS NULL OR @AMOUNT<=0
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
		RETURN -1;
	END 
	-- check for fraud
	IF @error = 0
	BEGIN
		EXEC dbo.sp_int_checkFraudWriteOff @amount = @AMOUNT, -- decimal
		    @svcid = @SVCID, -- int
		    @userid = @USERID, -- int
		    @error = @error OUTPUT -- int
	END
	
	BEGIN TRANSACTION T_WRITEOFF
	
	if 	@cbt = 0
			SELECT @balance = SUM(sa.amount) 
			FROM dbo.SubAccounts sa
			inner join PaymentSystems ps
			on sa.systemid = ps.id
			WHERE sa.accid = @ACCID AND sa.systemid <> @cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)
		else
			SELECT @balance = SUM(dbo.SubAccounts.amount) FROM dbo.SubAccounts WHERE accid = @ACCID AND systemid = @cbtpsid

	EXEC dbo.sp_int_trace 'Current balance', @balance

	IF @ERROR = 0
	BEGIN
		--учитываем резерв если имеется
		declare @reservedAmount decimal
		select @reservedAmount = sum(amount) from WriteOffReserve where accountId = @ACCID and cbt = @cbt

		if (@balance IS NULL or (@balance - isnull(@reservedAmount, 0)) < @AMOUNT)
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_OVERDRAFT');
	END
    
    IF @ERROR = 0
	BEGIN
    
        EXEC dbo.sp_int_trace 'Try to create new operation', @balance
    
		-- INSERT  NEW OPERATION ===========================
		INSERT INTO DBO.OPERATIONS (AMOUNT, USERID, EXECUTEDAT, TYPE, SRCACCID, SERVICEID, REASON)
			VALUES (@AMOUNT, @USERID, GETDATE(), @TYPE, @ACCID, @SVCID, @REASON)
		
		IF @@ERROR <> 0
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
		ELSE
			SELECT @OPERID = SCOPE_IDENTITY();
	END

	IF @ERROR = 0
	BEGIN
		DECLARE @AMTWK decimal(15,2);
		SET @AMTWK = @AMOUNT;
		DECLARE @SID INT, @SAMMOUNT decimal(15,2), @SYSTEMID INT, @priority int;


		WHILE( @AMTWK > 0 AND @ERROR=0)
		BEGIN
            
			SELECT TOP 1 @SID = SC.ID, @SAMMOUNT = SC.AMOUNT, @SYSTEMID = SC.SYSTEMID, @priority = PS.priority from dbo.SubAccounts AS SC, dbo.PaymentSystems as PS	
				WHERE SC.AMOUNT > 0 AND SC.ACCID = @ACCID AND SC.SYSTEMID = PS.ID AND 
					 ((@cbt=0 AND SYSTEMID<>@cbtpsid and (ps.ownSvcId is null or ps.ownSvcId = @SVCID)) OR (@cbt<>0 AND SYSTEMID=@cbtpsid))
				ORDER BY PS.priority ASC
            
                        
           	IF (@SID IS NULL)
            	SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTED');
            
            IF @error=0
            BEGIN
                DECLARE @ToWriteOff decimal(15,2);
                IF @AMTWK < @SAMMOUNT
                    SELECT @ToWriteOff = @AMTWK;
                ELSE
                    SELECT @ToWriteOff = @SAMMOUNT;                     
                
                EXEC dbo.sp_int_trace 'Try to write off: sub account/amount/systemid', @SID, @ToWriteOff, @SYSTEMID 

            	EXEC dbo.sp_int_writeOff_acc_sub @OPERID, @SID, @ToWriteOff, @error OUTPUT;
				
				--add record for royalty calculation
				INSERT WriteOffsPaymentSystem(operationId, paymentSystemId, amount)
					VALUES (@OPERID, @SYSTEMID, @ToWriteOff)

				if (@priority > 2)
				BEGIN
					set @realAmount = @realAmount + @ToWriteOff
				END
               
                IF @ERROR = 0
                BEGIN
                    SELECT @AMTWK = @AMTWK - @ToWriteOff;
                    EXEC dbo.sp_int_trace 'Still to write off', @AMTWK  
                END
            END         			
		END
	END


	IF @ERROR = 0
	BEGIN
		COMMIT TRANSACTION T_WRITEOFF
		RETURN 0;
	END
	
	ROLLBACK TRANSACTION T_WRITEOFF 
	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_api_replenish]    Script Date: 09/08/2013 16:06:12 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_api_replenish]
	-- caller service id
	@svcid	int,
	-- user name
	@user varchar(80),
	-- account name. can be null. in this case main user account will be used
	@account varchar(50) = NULL,
	-- payment system name
	@paymentsystem varchar(80),
	-- amount
	@amount DECIMAL(15,2),
	--adding award money
	@award DECIMAL(15,2) = null,
	-- reason of operation
	@reason text,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SET NOCOUNT ON;
	SELECT @ERROR = 0;
	
	DECLARE @USERID INT;
	DECLARE @ACCOUNTID INT;
	DECLARE @MAINACCID INT;
	DECLARE @PAYMENTSYSTEMID INT;
	DECLARE @OPERID INT;
	declare @partnerId INT;
	
    -- check parameters
	IF @svcid IS NULL OR @USER IS NULL OR @PAYMENTSYSTEM IS NULL OR @amount IS NULL OR @amount<=0 OR @reason IS NULL
	BEGIN
		SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ARG');
	END 
	
    -- resolve user id
    IF @ERROR = 0
	BEGIN
		SELECT @USERID = ID, @MAINACCID = accid, @partnerId = partnerid FROM USERS WHERE USERS.NAME = @USER;
		IF @USERID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_USER');
	END

    -- resolve account id
	IF @ERROR = 0
	BEGIN
		IF NOT @ACCOUNT IS NULL -- account specified
			BEGIN
				SELECT @ACCOUNTID = OPID FROM dbo.vw_api_accountMap WHERE ACCNAME = @ACCOUNT;
				IF @ACCOUNTID IS NULL
					SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
			END
		ELSE -- use main account
			BEGIN
				declare @active bit
				SELECT @active = active FROM UserServices 
					WHERE userid = @USERID AND serviceid = @svcid
				IF ( @active IS NULL ) -- if record not exist, if service in template, auto-subscribe
				BEGIN
					exec sp_int_autoSubscribe @svcid = @svcid, @userid = @userid, @partnerId = @partnerId, @error = @ERROR OUTPUT
				END

				IF (@ERROR = 0)
				BEGIN
					--SELECT @ACCOUNTID = @MAINACCID;
					SELECT @ACCOUNTID = OPID FROM  dbo.vw_api_accountMap WHERE serviceId = @svcid and userid=@USERID;	
					IF @ACCOUNTID IS NULL
						SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_ACCOUNT');
				END
			END 
	END
        
    -- resolve payment system 
	IF @ERROR = 0
	BEGIN
		SELECT @PAYMENTSYSTEMID = ID FROM PAYMENTSYSTEMS WHERE PAYMENTSYSTEMS.NAME = @PAYMENTSYSTEM;
		IF @PAYMENTSYSTEMID IS NULL
			SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNKNOWN_PAYMENT_SYSTEM');
	END
	
	-- check for fraud
	IF @error = 0
	BEGIN
		EXEC dbo.sp_int_checkFraudPayment
			@amount = @AMOUNT, -- decimal
		    @svcid = @SVCID, -- int
		    @userid = @USERID, -- int
		    @error = @error OUTPUT -- int
	END

	IF @ERROR = 0
	BEGIN
		EXEC dbo.sp_int_trace 'Try to replenish: userid , accid, pms', @USERID, @ACCOUNTID, @PAYMENTSYSTEMID
		EXEC DBO.SP_INT_REPLENISH @USERID, @ACCOUNTID, @PAYMENTSYSTEMID, @AMOUNT, @award, 102, @REASON, @OPERID OUTPUT, @ERROR OUTPUT
	END
	
		-- log request ================================================================================
	DECLARE @errlog INT; 
	SELECT @errlog = 0;
	
	EXEC dbo.[sp_log_replenish] @svcid = @svcid, -- int
	    @userid = @USERID, -- int
	    @amount = @AMOUNT, -- decimal
	    @accid = @ACCOUNTID,
	    @systemid = @PAYMENTSYSTEMID,
	    @operationid = @OPERID, -- int
		
	    @user = @user, -- varchar(80)
	    @account = @account, -- varchar(50)
	    @paymentsystem = @paymentsystem, -- varchar(80)
	    
	    @reason = @REASON, -- text
	    @state = @ERROR, -- int
	    @error = @errlog OUTPUT
	
	IF @error = 0 AND @errlog<>0
	BEGIN
		SET @error = @errlog;
		EXEC dbo.sp_int_trace 'Error on add log record', @errlog
	END		
	-- end log request ============================================================================
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_int_promoActivate]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Limorov Andrey
-- Create date: 2010/03/15
-- Description:	Activates promocode
-- =============================================
CREATE PROCEDURE [dbo].[sp_int_promoActivate]
	@svcid INT,
	-- user id code
	@USERID INT,
	-- account code
	@ACCID INT,
	-- promo code 
	@PROMO VARCHAR(80),
	-- operation id
	@OPERID INT OUTPUT,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;
	DECLARE @SUBACCID INT;
 	DECLARE @bonusesps INT
 	DECLARE @AMOUNT DECIMAL(15,2);

	SELECT @bonusesps = dbo.sf_int_get_bonuses_ps();

	-- pre check for fraud
	IF @error = 0
	BEGIN
		EXEC dbo.sp_int_pre_checkFraudPromo @svcid = @svcid, -- int
											@userid = @USERID, -- int
											@error = @error OUTPUT -- int
	END
	
	IF @ERROR = 0
	BEGIN
		BEGIN TRANSACTION T_PROMO_ACTIVATE
		-- CHECK PROMOCODE ===========================
		IF @ERROR = 0
		BEGIN
			SELECT @AMOUNT = AMOUNT FROM DBO.PROMOCODES WHERE CODE = @PROMO AND OPERATIONID IS NULL;
		
			IF @AMOUNT IS NULL
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_INVALID_PROMO');
		END	
		
		-- execute replenishment op =======================
		IF @ERROR=0
		BEGIN
		-- try to apply start money
			EXEC dbo.sp_int_trace 'Try to do start replenish by', @AMOUNT
			EXEC dbo.sp_int_replenish @userid, @accid, @bonusesps, @AMOUNT, 103, 'Promo activation', @OPERID OUTPUT, @error OUTPUT
		END

		-- MARK PROMO ACTIVATED ===========================		
		IF @ERROR = 0
		BEGIN
			UPDATE DBO.PROMOCODES SET OPERATIONID = @OPERID
				WHERE CODE = @PROMO AND OPERATIONID IS NULL
			
			IF @@ROWCOUNT = 0
			BEGIN
				EXEC dbo.sp_int_trace 'Cannot find user profile', @userid, @@ERROR;
				SELECT @ERROR = DBO.SF_INT_GET_ERROR_CODE('E_UNEXPECTEND');
			END
		END
			
		IF @ERROR = 0
			COMMIT TRANSACTION T_PROMO_ACTIVATE
		ELSE
			ROLLBACK TRANSACTION T_PROMO_ACTIVATE
	END
	
	-- post check for fraud
	IF @error <> 0
	BEGIN
		EXEC dbo.sp_int_post_checkFraudPromo @svcid = @svcid, -- int
											@userid = @USERID, -- int
											@state = @error,
											@error = @error OUTPUT -- int
	END
	
	
	IF @ERROR = 0
		RETURN 0;

	RETURN -1
END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_payments_init_report]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Andrey V. Limorov
-- Create date: 2010/04/27
-- Update 1:    2010/05/05 (4 new parameters for transaction count and total amount)
-- Update 2:    2010/05/11 
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_payments_init_report]
	-- session id
	@spid INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL,
	-- from total amount
	@fromTotalAmount DECIMAL(15,2) = NULL,
	-- to total amount
	@toTotalAmount DECIMAL(15,2)  = NULL,
	-- from transaction count
	@fromTransactionCount INT  = NULL,
	-- to transaction count
	@toTransactionCount INT  = NULL,
	-- list of systems
	@systemIdList VARCHAR(8000) = NULL,
	-- mask of user name
	@userMask VARCHAR(80) = '%',
	-- list of groups
	@groupsList VARCHAR(8000) = NULL
AS
BEGIN
	IF @spid IS NULL
		SET @spid = @@SPID;
	
	
	-- INIT	
	-- -------------------------------------------------------------	
	EXEC dbo.sp_rpt_payments_fillGroups @spid,  @groupsList;		
	
	-- CHECK PARAMETERS	
	-- -------------------------------------------------------------
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
		
	-- check TotalAmount parameters
	IF(@fromTotalAmount IS NULL)
		SET @fromTotalAmount=0;
		
	IF(@toTotalAmount IS NULL)
		SET @toTotalAmount=9999999999999.99;
		
	-- check TransactionCount parameters
	IF(@fromTransactionCount IS NULL)
		SET @fromTransactionCount=0;
		
	IF(@toTransactionCount IS NULL)
		SET @toTransactionCount=10000000;
		
	-- check user mask
	IF (@userMask IS NULL)
		SET @userMask = '%'	

	
	-- FILL PAYMENT SYSTEMS
	-- -------------------------------------------------------------
	IF (NOT @systemIdList IS NULL)
		INSERT INTO ##tmp_rptPaymentsSystems 
			SELECT @spid, CAST(part AS INT) FROM [sf_int_split](@systemIdList,',')
	ELSE
		INSERT INTO ##tmp_rptPaymentsSystems 
			SELECT @spid, id FROM dbo.PaymentSystems WITH(NOLOCK)
			WHERE id<>1 AND id<>2

	
	-- calculate the range of previous period	
	DECLARE @fromDateOld DATETIME;
	SET @fromDateOld = @fromDate - (@toDate - @fromDate);	
	
	EXEC dbo.sp_int_trace 'Input parameters',@fromDate, @toDate, @fromDateOld, @userMask, @systemIdList, @groupsList

	-- создаем временную таблицу для отфильтрованных юзеров
	DECLARE @filteredUsers AS TABLE
	(
		userid INT,
		totalAmount DECIMAL(15,2) 
	)
	-- заполняем ее			
	INSERT INTO @filteredUsers 
		SELECT OP.userid , SUM(OP.amount) FROM Operations AS OP WITH(NOLOCK)
		INNER JOIN Users AS US WITH(NOLOCK) ON OP.userid=US.id
		INNER JOIN ##tmp_rptPaymentsSystems  AS PS WITH(NOLOCK) ON OP.systemid = PS.systemid
		WHERE
			OP.executedat BETWEEN @fromDate AND @toDate
			AND US.name LIKE @userMask
		GROUP BY OP.userid
		HAVING
			SUM(OP.amount) BETWEEN @fromTotalAmount AND @toTotalAmount
			AND COUNT(OP.amount) BETWEEN @fromTransactionCount AND @toTransactionCount

	-- get current user groups
	INSERT INTO ##tmp_rptPaymentsUsers
		
		SELECT @spid, PG.groupid, FU.userid, 1 FROM @filteredUsers AS FU
		INNER JOIN ##tmp_rptPaymentsGroups AS PG WITH(NOLOCK) ON PG.spid = @spid
		WHERE
		((PG.START IS NULL AND PG.finish IS NULL) OR
		((PG.finish IS NULL OR FU.totalAmount < PG.finish) AND 
		  (PG.start IS NULL OR FU.totalAmount >= PG.start)))

	-- заполняем эту же таблицу пользователями с прошлого периода
	DELETE FROM @filteredUsers
	
	INSERT INTO @filteredUsers 
		SELECT OP.userid , SUM(OP.amount) FROM Operations AS OP WITH(NOLOCK)
		INNER JOIN Users AS US WITH(NOLOCK) ON OP.userid=US.id
		INNER JOIN ##tmp_rptPaymentsSystems  AS PS WITH(NOLOCK) ON OP.systemid = PS.systemid
		WHERE
			OP.executedat BETWEEN @fromDateOld AND @fromDate
			AND US.name LIKE @userMask
		GROUP BY OP.userid
		HAVING
			SUM(OP.amount) BETWEEN @fromTotalAmount AND @toTotalAmount
			AND COUNT(OP.amount) BETWEEN @fromTransactionCount AND @toTransactionCount 
			
	INSERT INTO ##tmp_rptPaymentsUsers
		SELECT @spid, PG.groupid, FU.userid, 0 FROM @filteredUsers AS FU
		INNER JOIN ##tmp_rptPaymentsGroups AS PG WITH(NOLOCK) ON PG.spid = @spid
		WHERE
			((PG.START IS NULL AND PG.finish IS NULL) OR
			((PG.finish IS NULL OR FU.totalAmount < PG.finish) AND 
			 (PG.start IS NULL OR FU.totalAmount >= PG.start)))
	

END
GO
/****** Object:  StoredProcedure [dbo].[sp_rpt_expenses_init_report]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		Pavel Yermalovich
-- Create date: 2010/05/25
-- Description:	Retrieves base groups list

CREATE PROCEDURE [dbo].[sp_rpt_expenses_init_report]
	-- session id
	@spid INT = NULL,
	-- from date
	@fromDate DATETIME = NULL,
	-- to date
	@toDate DATETIME = NULL,
	-- from total amount
	@fromTotalAmount DECIMAL(15,2) = NULL,
	-- to total amount
	@toTotalAmount DECIMAL(15,2) = NULL,
	-- from transaction count
	@fromTransactionCount INT = NULL,
	-- to transaction count
	@toTransactionCount INT = NULL,
	-- list of games (services)
	@serviceIdList VARCHAR(8000) = NULL,
	-- list of subjects 
	@subjectList VARCHAR(8000) = NULL,
	-- mask of user names
	@userMask VARCHAR(80) = NULL,
	-- list of groups
	@groupsList VARCHAR(8000) = NULL
AS
BEGIN

	IF @spid IS NULL
		SET @spid = @@SPID;

	-- FILL GROUPS
	-- -------------------------------------------------------------
	EXEC sp_rpt_expenses_fillGroups @spid, @groupsList;
	
	-- CHECK PARAMETERS	
	-- -------------------------------------------------------------
	
	-- check data parameters
	IF (@toDate IS NULL)
		SET @toDate = CONVERT(DATETIME,'2100/01/01 00:00');
	IF (@fromDate IS NULL)
		SET @fromDate = DATEADD(YEAR,-90,@toDate)
	
	-- check TotalAmount parameters
	IF(@fromTotalAmount IS NULL)
		SET @fromTotalAmount=0;
		
	IF(@toTotalAmount IS NULL)
		SET @toTotalAmount=9999999999999.99;
		
	-- check TransactionCount parameters
	IF(@fromTransactionCount IS NULL)
		SET @fromTransactionCount=0;
		
	IF(@toTransactionCount IS NULL)
		SET @toTransactionCount=10000000;
		
	-- check user mask
	IF (@userMask IS NULL)
		SET @userMask = '%'	
	
	
	EXEC dbo.sp_int_trace 'Services list' , @serviceIdList

	-- FILL GAMES	
	-- -------------------------------------------------------------
	IF (@serviceIdList IS NOT NULL)
		BEGIN
			DECLARE @svl TABLE(pos INT, part varchar(80));
			INSERT INTO @svl
				EXEC dbo.sp_int_split @serviceIdList,',';
				
			INSERT INTO ##tmp_rptExpensesGames
				SELECT @spid, CAST(part AS INT)  AS serviceid 
				FROM @svl
		END			
	ELSE
		INSERT INTO ##tmp_rptExpensesGames
			SELECT @spid, id FROM dbo.Services
	
	EXEC dbo.sp_int_trace 'Subjects list' , @subjectList
	-- fill subjects
	IF (@subjectList IS NOT NULL)
		BEGIN
			DECLARE @sbl TABLE(pos INT, part varchar(80));
			INSERT INTO @sbl
				EXEC dbo.sp_int_split @subjectList,'|';
						
			INSERT INTO ##tmp_rptExpensesSubjects
				SELECT @spid, CAST(part AS NVARCHAR(80)) 
				FROM @sbl
		END		
	ELSE
		INSERT INTO ##tmp_rptExpensesSubjects
			SELECT DISTINCT @spid, CAST(reason AS NVARCHAR(80)) FROM dbo.Operations	
			WHERE	serviceid IS NOT NULL AND
					CAST(reason AS NVARCHAR(80)) IS NOT NULL AND
					type = 201 -- expense by user

	-- calculate the range of previous period
	DECLARE @fromDateOld DATETIME;
	SET @fromDateOld = @fromDate - (@toDate - @fromDate);	
	
	EXEC dbo.sp_int_trace 'Input parameters', @spid, @fromDate, @toDate, @userMask, @fromTotalAmount, @toTotalAmount
	EXEC dbo.sp_int_trace 'Input parameters', @fromTransactionCount, @toTransactionCount
	
	-- создаем временную таблицу для отфильтрованных юзеров
	DECLARE @filteredUsers AS TABLE
	(
		userid INT,
		totalAmount DECIMAL(15,2) 
	);
	-- заполняем ее			
	INSERT INTO @filteredUsers 
		-- User ID, Сумма трат по юзеру
		SELECT OP.userid , SUM(OP.amount) FROM Operations AS OP
		-- присоединение для поиска по маске
		INNER JOIN Users AS US ON OP.userid=US.id
		WHERE
			-- filter by expense only
			OP.type = 201
			--фильтрация по дате
			AND OP.executedat BETWEEN @fromDate AND @toDate
			--по маске
			AND US.name LIKE @userMask
			--по играм
			AND OP.serviceid IN (SELECT serviceid FROM ##tmp_rptExpensesGames WHERE spid=@spid)
			AND CAST(OP.reason AS NVARCHAR(80)) IN (SELECT reason FROM ##tmp_rptExpensesSubjects WHERE spid=@spid)
		GROUP BY OP.userid
		--фильтрация по кол-ву транзакций и выплаченных денег
		HAVING
			SUM(OP.amount) BETWEEN @fromTotalAmount AND @toTotalAmount
			AND COUNT(OP.amount) BETWEEN @fromTransactionCount AND @toTransactionCount ;
	
    -- get current user groups
	INSERT INTO ##tmp_rptExpensesUsers
		
		SELECT @spid, EG.groupid, FU.userid, 1 FROM @filteredUsers AS FU
		INNER JOIN ##tmp_rptExpensesGroups AS EG ON EG.spid = @spid AND
		((EG.START IS NULL AND EG.finish IS NULL) OR
		  ((EG.finish IS NULL OR FU.totalAmount < EG.finish) AND 
		   (EG.start IS NULL OR FU.totalAmount >= EG.start)))

	-- заполняем эту же таблицу пользователями с прошлого периода
	DELETE FROM @filteredUsers
	
	INSERT INTO @filteredUsers 
	
		SELECT OP.userid , SUM(OP.amount) FROM Operations AS OP
		INNER JOIN ##tmp_rptExpensesUsers AS EU ON OP.userid=EU.userid
		INNER JOIN Users AS US ON EU.userid = US.id
		WHERE
			-- filter by expense only
			OP.type = 201
			AND EU.spid = @spid AND EU.periodid = 1 
			AND OP.executedat BETWEEN @fromDateOld AND @fromDate
			AND US.name LIKE @userMask
			AND OP.serviceid IN (SELECT serviceid FROM ##tmp_rptExpensesGames)
			AND CAST(OP.reason AS NVARCHAR(80)) IN (SELECT reason FROM ##tmp_rptExpensesSubjects) 
		GROUP BY OP.userid
		HAVING
			SUM(OP.amount) BETWEEN @fromTotalAmount AND @toTotalAmount
			AND COUNT(OP.amount) BETWEEN @fromTransactionCount AND @toTransactionCount 
			
	INSERT INTO ##tmp_rptExpensesUsers
		
		SELECT @spid, EG.groupid, FU.userid, 0 AS periodid FROM @filteredUsers AS FU
		INNER JOIN ##tmp_rptExpensesGroups AS EG ON EG.spid = @spid AND
		((EG.START IS NULL AND EG.finish IS NULL) OR
		  ((EG.finish IS NULL OR FU.totalAmount < EG.finish) AND 
		   (EG.start IS NULL OR FU.totalAmount >= EG.start)))
	
END
GO
/****** Object:  StoredProcedure [dbo].[sp_legacy_replenish]    Script Date: 09/08/2013 16:06:13 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[sp_legacy_replenish]
	-- caller service id
	@svcid	int,
	-- user name
	@user varchar(80),
	-- amount
	@amount DECIMAL(15,2),
	-- reason of operation
	@reason text,
	-- error code
	@error int OUTPUT
AS
BEGIN
	SELECT @ERROR = 0;

	DECLARE @legacyps VARCHAR(80);
	SELECT @legacyps = name FROM dbo.PaymentSystems WHERE id = dbo.sf_int_get_legacy_ps();
	
	IF @ERROR = 0
		EXEC dbo.sp_api_replenish @svcid, @user, NULL, @legacyps, @amount, null, @reason, @error OUTPUT
	  
	IF @ERROR = 0
	BEGIN
		RETURN 0;
	END

	RETURN -1
END
GO
/****** Object:  Check [CK_amount]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[SubAccounts]  WITH NOCHECK ADD  CONSTRAINT [CK_amount] CHECK  (([amount]>=(0)))
GO
ALTER TABLE [dbo].[SubAccounts] CHECK CONSTRAINT [CK_amount]
GO
/****** Object:  ForeignKey [R_47]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Accounts]  WITH NOCHECK ADD  CONSTRAINT [R_47] FOREIGN KEY([userid])
REFERENCES [dbo].[Users] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[Accounts] CHECK CONSTRAINT [R_47]
GO
/****** Object:  ForeignKey [R_40]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [R_40] FOREIGN KEY([groupid])
REFERENCES [dbo].[EmployeeGroups] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [R_40]
GO
/****** Object:  ForeignKey [R_42]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[LegacyServices]  WITH CHECK ADD  CONSTRAINT [R_42] FOREIGN KEY([serviceid])
REFERENCES [dbo].[Services] ([id])
GO
ALTER TABLE [dbo].[LegacyServices] CHECK CONSTRAINT [R_42]
GO
/****** Object:  ForeignKey [R_18]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Operations]  WITH NOCHECK ADD  CONSTRAINT [R_18] FOREIGN KEY([userid])
REFERENCES [dbo].[Users] ([id])
GO
ALTER TABLE [dbo].[Operations] CHECK CONSTRAINT [R_18]
GO
/****** Object:  ForeignKey [R_21]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Operations]  WITH NOCHECK ADD  CONSTRAINT [R_21] FOREIGN KEY([type])
REFERENCES [dbo].[OperationTypes] ([id])
GO
ALTER TABLE [dbo].[Operations] CHECK CONSTRAINT [R_21]
GO
/****** Object:  ForeignKey [R_22]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Operations]  WITH NOCHECK ADD  CONSTRAINT [R_22] FOREIGN KEY([srcaccid])
REFERENCES [dbo].[Accounts] ([id])
GO
ALTER TABLE [dbo].[Operations] CHECK CONSTRAINT [R_22]
GO
/****** Object:  ForeignKey [R_23]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Operations]  WITH NOCHECK ADD  CONSTRAINT [R_23] FOREIGN KEY([destaccid])
REFERENCES [dbo].[Accounts] ([id])
GO
ALTER TABLE [dbo].[Operations] CHECK CONSTRAINT [R_23]
GO
/****** Object:  ForeignKey [R_29]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Operations]  WITH NOCHECK ADD  CONSTRAINT [R_29] FOREIGN KEY([empid])
REFERENCES [dbo].[Employees] ([id])
GO
ALTER TABLE [dbo].[Operations] CHECK CONSTRAINT [R_29]
GO
/****** Object:  ForeignKey [R_30]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Operations]  WITH NOCHECK ADD  CONSTRAINT [R_30] FOREIGN KEY([systemid])
REFERENCES [dbo].[PaymentSystems] ([id])
GO
ALTER TABLE [dbo].[Operations] CHECK CONSTRAINT [R_30]
GO
/****** Object:  ForeignKey [R_46]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Operations]  WITH NOCHECK ADD  CONSTRAINT [R_46] FOREIGN KEY([serviceid])
REFERENCES [dbo].[Services] ([id])
GO
ALTER TABLE [dbo].[Operations] CHECK CONSTRAINT [R_46]
GO
/****** Object:  ForeignKey [R_17]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Profiles]  WITH NOCHECK ADD  CONSTRAINT [R_17] FOREIGN KEY([userid])
REFERENCES [dbo].[Users] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[Profiles] CHECK CONSTRAINT [R_17]
GO
/****** Object:  ForeignKey [R_28]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Profiles]  WITH NOCHECK ADD  CONSTRAINT [R_28] FOREIGN KEY([templateid])
REFERENCES [dbo].[Templates] ([id])
GO
ALTER TABLE [dbo].[Profiles] CHECK CONSTRAINT [R_28]
GO
/****** Object:  ForeignKey [R_27]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Promocodes]  WITH CHECK ADD  CONSTRAINT [R_27] FOREIGN KEY([operationid])
REFERENCES [dbo].[Operations] ([id])
GO
ALTER TABLE [dbo].[Promocodes] CHECK CONSTRAINT [R_27]
GO
/****** Object:  ForeignKey [R_44]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[ProtocolPaymentSystems]  WITH CHECK ADD  CONSTRAINT [R_44] FOREIGN KEY([systemid])
REFERENCES [dbo].[PaymentSystems] ([id])
GO
ALTER TABLE [dbo].[ProtocolPaymentSystems] CHECK CONSTRAINT [R_44]
GO
/****** Object:  ForeignKey [R_43]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[ProtocolServices]  WITH CHECK ADD  CONSTRAINT [R_43] FOREIGN KEY([serviceid])
REFERENCES [dbo].[Services] ([id])
GO
ALTER TABLE [dbo].[ProtocolServices] CHECK CONSTRAINT [R_43]
GO
/****** Object:  ForeignKey [R_15]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[ReferalCodes]  WITH CHECK ADD  CONSTRAINT [R_15] FOREIGN KEY([partnerid])
REFERENCES [dbo].[PartnerPrograms] ([id])
GO
ALTER TABLE [dbo].[ReferalCodes] CHECK CONSTRAINT [R_15]
GO
/****** Object:  ForeignKey [R_25]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Services]  WITH CHECK ADD  CONSTRAINT [R_25] FOREIGN KEY([currencyid])
REFERENCES [dbo].[Currencies] ([id])
GO
ALTER TABLE [dbo].[Services] CHECK CONSTRAINT [R_25]
GO
/****** Object:  ForeignKey [R_24]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Sessions]  WITH CHECK ADD  CONSTRAINT [R_24] FOREIGN KEY([usrservid])
REFERENCES [dbo].[UserServices] ([id])
GO
ALTER TABLE [dbo].[Sessions] CHECK CONSTRAINT [R_24]
GO
/****** Object:  ForeignKey [R_14]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[SubAccounts]  WITH NOCHECK ADD  CONSTRAINT [R_14] FOREIGN KEY([accid])
REFERENCES [dbo].[Accounts] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[SubAccounts] CHECK CONSTRAINT [R_14]
GO
/****** Object:  ForeignKey [R_8]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[SubAccounts]  WITH NOCHECK ADD  CONSTRAINT [R_8] FOREIGN KEY([systemid])
REFERENCES [dbo].[PaymentSystems] ([id])
GO
ALTER TABLE [dbo].[SubAccounts] CHECK CONSTRAINT [R_8]
GO
/****** Object:  ForeignKey [R_19]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Transactions]  WITH NOCHECK ADD  CONSTRAINT [R_19] FOREIGN KEY([operationid])
REFERENCES [dbo].[Operations] ([id])
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[Transactions] CHECK CONSTRAINT [R_19]
GO
/****** Object:  ForeignKey [R_20]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Transactions]  WITH NOCHECK ADD  CONSTRAINT [R_20] FOREIGN KEY([subaccid])
REFERENCES [dbo].[SubAccounts] ([id])
GO
ALTER TABLE [dbo].[Transactions] CHECK CONSTRAINT [R_20]
GO
/****** Object:  ForeignKey [R_13]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Users]  WITH NOCHECK ADD  CONSTRAINT [R_13] FOREIGN KEY([accid])
REFERENCES [dbo].[Accounts] ([id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [R_13]
GO
/****** Object:  ForeignKey [R_16]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[Users]  WITH NOCHECK ADD  CONSTRAINT [R_16] FOREIGN KEY([partnerid])
REFERENCES [dbo].[PartnerPrograms] ([id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [R_16]
GO
/****** Object:  ForeignKey [R_12]    Script Date: 09/08/2013 16:06:11 ******/
ALTER TABLE [dbo].[UserServices]  WITH NOCHECK ADD  CONSTRAINT [R_12] FOREIGN KEY([accountid])
REFERENCES [dbo].[Accounts] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[UserServices] CHECK CONSTRAINT [R_12]
GO
