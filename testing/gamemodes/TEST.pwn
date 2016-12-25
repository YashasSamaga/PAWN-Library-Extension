#define SCRIPT_IDENTIFIER "gamemode"

#include <a_samp>
#include <PLE/string>
#include <PLE/math>
#include <PLE/time>
#include <PLE/isc>
/*****************************************************************************************************************/
public PublicVarA = 1027;
public PublicVar = 1027;
public PublicVarB = 1027;
native sbsearch(search[], source[][], &idx, size_major = sizeof(source), size_minor = sizeof(source[]));
native ibsearch(key, array[], &idx, size = sizeof(array));
native fbsearch(Float:key, Float:array[], &idx, size = sizeof(array));

String()
{
    new str[256] = "memmove can be very useful......";
    new str2[256] = "This is string two!";
    new str3[5];
PublicVar = PublicVarA = PublicVarB;
  	memmove(str[20], str[15], 11);
  	if(strcmp("memmove can be very very useful.", str)) print("[TEST1] memmove failed.");

    strcpy(str, str2);
    if(strcmp(str, "This is string two!")) print("[TEST2] strcpy failed.");

    strcpy(str3, str2);
    if(strcmp(str3, "This")) print("[TEST3] strcpy failed.");

    strncpy(str3, str2, 5);
    if(strcmp(str3, "This")) print("[TEST4] strncpy failed.");

    strncat(str, str2, 3);
    if(strcmp(str,"This is string two!Thi" )) print("[TEST5] strncat failed.");
    
    if(strncmp("This AAA","This BBBB", 4)) print("[TEST6] strncmp failed.");
    
    if(!strncmp("Thhs AAA","This BBBB", 4)) print("[TEST7] strncmp failed.");
    
    if(memchr("This is a test string\0asdasdasdasd", 0, 30) != 21) print("[TEST8] memchr failed.");
    
    if(strchr("This is a test string", 'g', 0) != 20) print("[TEST9] strchr failed.");
 
  	if(strcspn("abcd5efghidjk", "1234567890") != 4) print("[TEST10] strcspn failed.");
  
    if(strpbrk("abcd5efghidjk", "1234567890") != '5') print("[TEST11] strpbrk failed.");
    
    if(strrchr("abcd5efghidjk", 'd') != 10) print("[TEST12] strrchar failed.");
    
    if(strspn("abcdezxccccfasy", "abcdefhiklsz") != 6) print("[TEST13] strspn failed.");
    
    new idx = 2;
    strtok(str2, str, idx, " i");
    
    if(strcmp(str, "s") || idx != 4) print("[TEST14] strtok failed.");
    
    memset(str, 'i', 6);
    if(str[6] != 's' || str[1] != 'i') print("[TEST15] memset failed.");
    
    new msg[256] = "abc efg hij lmknabc abcse abcy abc";
    if(strreplace(msg, "abc", "***") != true) print("[TEST17] strreplace failed.");
    
    if(strcmp(msg, "*** efg hij lmkn*** ***se ***y ***")) print("[TEST18] strreplace failed.");

	new trim[] = "   abc   ";
	if(strtrim(trim) != 3) print("[TEST19] strtrim failed.");

    if(strcmp(trim, "abc")) print("[TEST20] strtrim failed.");

    if(strtoupper(trim) != 3) print("[TEST21] strtoupper failed.");
    if(strcmp(trim, "ABC")) print("[TEST22] strtoupper failed.");

    if(strtolower(trim) != 3) print("[TEST23] strtolower failed.");
    if(strcmp(trim, "abc")) print("[TEST24] strtolower failed.");
}
Time()
{
	new mytime[time_t];
	now(mytime);
	
	printf("second:%d minute:%d hour:%d day:%d month:%d year:%d wday:%d yday:%d dst:%d", mytime[second], mytime[minute], mytime[hour], mytime[day], mytime[month], mytime[year], mytime[wday], mytime[yday], mytime[isdst]);
	
	new mytime2[time_t];
	createtime(gettime() + 120, mytime2);
	printf("second:%d minute:%d hour:%d day:%d month:%d year:%d wday:%d yday:%d dst:%d", mytime2[second], mytime2[minute], mytime2[hour], mytime2[day], mytime2[month], mytime2[year], mytime2[wday], mytime2[yday], mytime2[isdst]);
	
	if(gettimestamp(mytime2) != (gettime() + 120)) print("[TEST] gettimestamp failed.");
	
	createtime(difftime(mytime2, mytime), mytime);
	printf("second:%d minute:%d hour:%d day:%d month:%d year:%d wday:%d yday:%d dst:%d", mytime[second], mytime[minute], mytime[hour], mytime[day], mytime[month], mytime[year], mytime[wday], mytime[yday], mytime[isdst]);

	new result[256];
	asctime(mytime, result);
	print(result);

	strftime(mytime, "Time Remaining: %M:%p", result);
	print(result);
}
main ()
{
	String();
	Time();
}
forward RandomPublic(num, str[], str2[]);
public RandomPublic(num, str[], str2[])
{
//	printf("%d %s %s", num, str, str2);
}
public OnScriptInit(scriptKey, scriptIdentifier[])
{
	printf("[GAMEMODE] OnScriptInit >> ScriptKey: %d ScriptIdentifier: %s", scriptKey, scriptIdentifier);

	if(IsValidScript(6)) print("[TEST1] IsValidScript failed.");
	if(!IsValidScript(1)) print("[TEST2] IsValidScript failed.");

	if(GetScriptType(0) != SCRIPT_SUPPORTED) print("[TEST3] GetScriptType failed.");
	if(GetScriptPoolSize() != 2) print("[TEST4] GetScriptPoolSize failed.");

	new sid[SCRIPT_IDENTIFIER_SIZE];
 	GetScriptIdentifierFromKey(GetScriptKey(), sid);

 	if(strcmp(SCRIPT_IDENTIFIER, sid)) print("[TEST5] GetScriptIdentifierFromID failed.");

 	new ids[16];
	if(GetScriptKeyFromIdentifier("gamemode", ids) == 2) print("[TEST6] GetScriptIDFromIdentifier failed.");
	if(ids[0] != GetScriptKey()) print("[TEST7] GetScriptIDFromIdentifier failed.");
}
public OnScriptExit(scriptKey, scriptIdentifier[])
{
    printf("[GAMEMODE] OnScriptExit >> ScriptKey: %d ScriptIdentifier: %s", scriptKey, scriptIdentifier);
}


