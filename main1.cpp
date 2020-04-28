/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2019-2020                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
    NONE_CMD = -2,
    COMMENT_CMD = -1,
    INIT_CMD = 0,
	ADDARTIST_CMD = 1,
	REMOVEARTIST_CMD = 2,
	ADDTOSONGCOUNT_CMD = 3,
	NUMBEROFSTREAMS_CMD = 4,
	GETRECOMMENDEDSONGS_CMD = 5,
    QUIT_CMD = 6
} commandType;

static const int numActions = 9;
static const char *commandStr[] = {
        "Init",
        "AddArtist",
        "RemoveArtist",
        "AddToSongCount",
        "NumberOfStreams",
        "GetRecommendedSongs",
        "Quit" };

static const char* ReturnValToStr(int val) {
    switch (val) {
        case SUCCESS:
            return "SUCCESS";
        case ALLOCATION_ERROR:
            return "ALLOCATION_ERROR";
        case FAILURE:
            return "FAILURE";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "";
    }
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
    error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString,ErrorParams) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString, ErrorParams); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {

    char buffer[MAX_STRING_INPUT_SIZE];

    // Reading commands
    while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
        fflush(stdout);
        if (parser(buffer) == error)
            break;
    };
    return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
                                const char** const command_arg) {
    if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
        return (NONE_CMD);
    if (StrCmp("#", command)) {
        if (strlen(command) > 1)
            printf("%s", command);
        return (COMMENT_CMD);
    };
    for (int index = 0; index < numActions; index++) {
        if (StrCmp(commandStr[index], command)) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return ((commandType)index);
        };
    };
    return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddArtist(void* DS, const char* const command);
static errorType OnRemoveArtist(void* DS, const char* const command);
static errorType OnAddToSongCount(void* DS, const char* const command);
static errorType OnNumberOfStreams(void* DS, const char* const command);
static errorType OnGetRecommendedSongs(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;

    commandType command_val = CheckCommand(command, &command_args);
	
    switch (command_val) {

        case (INIT_CMD):
            rtn_val = OnInit(&DS, command_args);
            break;
        case (ADDARTIST_CMD):
            rtn_val = OnAddArtist(DS, command_args);
            break;
        case (REMOVEARTIST_CMD):
            rtn_val = OnRemoveArtist(DS, command_args);
            break;
        case (ADDTOSONGCOUNT_CMD):
            rtn_val = OnAddToSongCount(DS, command_args);
            break;
        case (NUMBEROFSTREAMS_CMD):
            rtn_val = OnNumberOfStreams(DS, command_args);
            break;
        case (GETRECOMMENDEDSONGS_CMD):
            rtn_val = OnGetRecommendedSongs(DS, command_args);
            break;
        case (QUIT_CMD):
            rtn_val = OnQuit(&DS, command_args);
            break;

        case (COMMENT_CMD):
            rtn_val = error_free;
            break;
        case (NONE_CMD):
            rtn_val = error;
            break;
        default:
            assert(false);
            break;
    };
    return (rtn_val);
}

static errorType OnInit(void** DS, const char* const command) {
    if (isInit) {
        printf("init was already called.\n");
        return (error_free);
    };
    isInit = true;

    ValidateRead(0, 0, "%s failed.\n", commandStr[INIT_CMD]);
    *DS = Init();

    if (*DS == NULL) {
        printf("init failed.\n");
        return error;
    };

    printf("init done.\n");
    return error_free;
}

static errorType OnAddArtist(void* DS, const char* const command) {
    int artistID, numOfSongs;
    ValidateRead(sscanf(command, "%d %d", &artistID, &numOfSongs), 2, "%s failed.\n", commandStr[ADDARTIST_CMD]);
    StatusType res = AddArtist(DS, artistID, numOfSongs);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[ADDARTIST_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[ADDARTIST_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnRemoveArtist(void* DS, const char* const command) {
    int artistID;
    ValidateRead(sscanf(command, "%d", &artistID), 1, "%s failed.\n", commandStr[REMOVEARTIST_CMD]);
	StatusType res = RemoveArtist(DS, artistID);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[REMOVEARTIST_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[REMOVEARTIST_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnAddToSongCount(void* DS, const char* const command) {
    int artistID, songID;
    ValidateRead(sscanf(command, "%d %d", &artistID, &songID), 2, "%s failed.\n", commandStr[ADDTOSONGCOUNT_CMD]);
    StatusType res = AddToSongCount(DS, artistID, songID);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[ADDTOSONGCOUNT_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[ADDTOSONGCOUNT_CMD], ReturnValToStr(res));
    return error_free;
}

static errorType OnNumberOfStreams(void* DS, const char* const command) {
	int artistID, songID, streams;
    ValidateRead(sscanf(command, "%d %d", &artistID, &songID), 2, "%s failed.\n", commandStr[NUMBEROFSTREAMS_CMD]);
    StatusType res = NumberOfStreams(DS, artistID, songID, &streams);

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[NUMBEROFSTREAMS_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %d\n", commandStr[NUMBEROFSTREAMS_CMD], streams);
    return error_free;
}

static errorType OnGetRecommendedSongs(void* DS, const char* const command) {
    int numOfSongs;
    int *artists, *songs;

	artists = (int *)malloc(numOfSongs * sizeof(int));
	songs = (int *)malloc(numOfSongs * sizeof(int));

    ValidateRead(sscanf(command, "%d", &numOfSongs), 1, "%s failed.\n", commandStr[GETRECOMMENDEDSONGS_CMD]);
	StatusType res;
	if (artists != NULL && songs != NULL) {
		res = GetRecommendedSongs(DS, numOfSongs, artists, songs);
	}
	else {
		res = ALLOCATION_ERROR;
	}

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[GETRECOMMENDEDSONGS_CMD], ReturnValToStr(res));
        return error_free;
    }

    printf("%s: %s\n", commandStr[GETRECOMMENDEDSONGS_CMD], ReturnValToStr(res));

	printf("Artist\t|\tSong\n");

    for (int i = 0; i < numOfSongs; i++)
    {
        printf("%d\t|\t%d\n", artists[i], songs[i]);
    }

    printf("--End of recommended songs--\n");

	if (artists != NULL) free(artists);
	if (songs != NULL) free(songs);

    return error_free;
}

static errorType OnQuit(void** DS, const char* const command) {
    Quit(DS);
    if (*DS != NULL) {
        printf("quit failed.\n");
        return error;
    };

    isInit = false;
    printf("quit done.\n");
    return error_free;
}

#ifdef __cplusplus
}
#endif
