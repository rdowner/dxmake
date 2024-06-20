Prototype char *AllocPathBuffer(void);
Prototype void FreePathBuffer(char *);
Prototype void InitCmdList(void);
Prototype void PutCmdListChar(List *, char);
Prototype void InsCmdListChar(List *, char);
Prototype void PutCmdListSym(List *, char *, short *);
Prototype void CopyCmdList(List *, List *);
Prototype void FreeCmdList(List *);
Prototype void AppendCmdList(List *, List *);
Prototype int  PopCmdListSym(List *, char *, long);
Prototype int  PopCmdListChar(List *);
Prototype void CopyCmdListBuf(List *, char *);
Prototype void CopyCmdListNewLineBuf(List *, char *);
Prototype long CmdListSize(List *);
Prototype long CmdListSizeNewLine(List *);
Prototype void CopyCmdListConvert(List *, List *, char *, char *);
Prototype long ExecuteCmdList(DepNode *, List *);
Prototype int  WildConvert(char *, char *, char *, char *);
Prototype void InitDep(void);
Prototype DepRef  *CreateDepRef(List *, char *);
Prototype DepCmdList *AllocDepCmdList(void);
Prototype DepRef  *DupDepRef(DepRef *);
Prototype void    IncorporateDependency(DepRef *, DepRef *, List *);
Prototype int     ExecuteDependency(DepNode *parent, DepRef *lhs, int how);
Prototype List DepList;
Prototype List  DoList;
Prototype short DDebug;
Prototype short NoRunOpt;
Prototype short ExitCode;
Prototype short DoAll;
Prototype short SomeWork;
Prototype short NParallel;
Prototype void InitParser(void);
Prototype void ParseFile(char *);
Prototype token_t ParseAssignment(char *, token_t, int, char);
Prototype token_t ParseDependency(char *, token_t);
Prototype token_t GetElement(int ifTrue, int *expansion);
Prototype void    ParseVariable(List *, short);
Prototype char   *ParseVariableBuf(List *, ubyte *, short);
Prototype char   *ExpandVariable(ubyte *, List *);
Prototype token_t GetToken(void);
Prototype void expect(token_t, token_t);
Prototype void error(short, const char *, ...);
Prototype char SymBuf[256];
Prototype long LineNo;
Prototype long Execute_Command(char *, short);
Prototype void InitCommand(void);
Prototype long LoadSegLock(long, char *);
Prototype void InitVar(void);
Prototype Var *MakeVar(char *, char);
Prototype Var *FindVar(char *, char);
Prototype void AppendVar(Var *, char *, long);
Prototype void InsertVar(Var *, char *, long);
Prototype int pushIf(IfNode **ifBase, int value);
Prototype int popIf(IfNode **ifBase);
Prototype int elseIf(IfNode **ifBase);
