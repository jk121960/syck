/* Generated by re2c 0.5 on Tue Apr 22 02:16:57 2003 */
#line 1 "lib/token.re"
//
// token.re
//
// $Author$
// $Date$
//
// Copyright (C) 2003 why the lucky stiff
//

#include "syck.h"
#include "gram.h"

//
// Allocate quoted strings in chunks
//
#define QUOTELEN    1024

//
// They do my bidding...
//
#define YYCTYPE     char
#define YYCURSOR    parser->cursor
#define YYMARKER    parser->marker
#define YYLIMIT     parser->limit
#define YYTOKEN     parser->token
#define YYTOKTMP    parser->toktmp
#define YYLINEPTR   parser->lineptr
#define YYLINE      parser->linect
#define YYFILL(n)   syck_parser_read(parser)

//
// Repositions the cursor at `n' offset from the token start.
// Only works in `Header' and `Document' sections.
//
#define YYPOS(n)    YYCURSOR = YYTOKEN + n

//
// Track line numbers
//
#define NEWLINE(ptr)    YYLINE++; YYLINEPTR = ptr + 1

//
// I like seeing the level operations as macros...
//
#define ADD_LEVEL(len, status)  syck_parser_add_level( parser, len, status )
#define POP_LEVEL()     syck_parser_pop_level( parser )
#define CURRENT_LEVEL() syck_parser_current_level( parser )

//
// Force a token next time around yylex()
//
#define FORCE_NEXT_TOKEN(tok)    parser->force_token = tok;

//
// Nice little macro to ensure we're IOPENed to the current level.
// * Only use this macro in the "Document" section *
//
#define ENSURE_IOPEN(last_lvl, to_len, reset) \
        if ( last_lvl->spaces < to_len ) \
        { \
            if ( last_lvl->status == syck_lvl_inline ) \
            { \
                goto Document; \
            } \
            else \
            { \
                ADD_LEVEL( to_len, syck_lvl_doc ); \
                if ( reset == 1 ) YYPOS(0); \
                return IOPEN; \
            } \
        } 

//
// Nice little macro to ensure closure of levels.
// * Only use this macro in the "Document" section *
//
#define ENSURE_IEND(last_lvl, to_len) \
        if ( last_lvl->spaces > to_len ) \
        { \
            syck_parser_pop_level( parser ); \
            YYPOS(0); \
            return IEND; \
        }

//
// Concatenates quoted string items and manages allocation
// to the quoted string
//
#define QUOTECAT(s, c, i, l) \
        { \
            if ( i + 1 >= c ) \
            { \
                c += QUOTELEN; \
                S_REALLOC_N( s, char, c ); \
            } \
            s[i++] = l; \
            s[i] = '\0'; \
        }

//
// Tags a plain scalar with a transfer method
// * Use only in "Plain" section *
//
#define RETURN_IMPLICIT() \
    { \
        YYCURSOR = YYTOKTMP; \
        yylval->nodeData = syck_new_str2( YYTOKEN, YYCURSOR - YYTOKEN ); \
        if ( parser->implicit_typing == 1 ) \
        { \
            try_tag_implicit( yylval->nodeData, parser->taguri_expansion ); \
        } \
        return PLAIN; \
    }

//
// Handles newlines, calculates indent
//
#define GOBBLE_UP_INDENT( ict, start ) \
    char *indent = start; \
    NEWLINE(indent); \
    while ( indent < YYCURSOR ) \
    { \
        if ( *(++indent) == '\n' ) \
        { \
            NEWLINE(indent); \
        } \
    } \
    ict = 0; \
    if ( *YYCURSOR == '\0' ) \
    { \
        ict = -1; \
        start = YYCURSOR; \
    } \
    else if ( *YYLINEPTR == ' ' ) \
    { \
        ict = YYCURSOR - YYLINEPTR; \
    }

//
// Argjh!  I hate globals!  Here for yyerror() only!
//
SyckParser *syck_parser_ptr = NULL;

//
// My own re-entrant yylex() using re2c.
// You really get used to the limited regexp.
// It's really nice to not rely on backtracking and such.
//
int
yylex( YYSTYPE *yylval, SyckParser *parser )
{
    syck_parser_ptr = parser;
    if ( YYCURSOR == NULL ) 
    {
        syck_parser_read( parser );
    }

    if ( parser->force_token != 0 )
    {
        int t = parser->force_token;
        parser->force_token = 0;
        return t;
    }

#line 180


    if ( YYLINEPTR != YYCURSOR )
    {
        goto Document;
    }

Header:

    YYTOKEN = YYCURSOR;

{
	YYCTYPE yych;
	unsigned int yyaccept;
	static unsigned char yybm[] = {
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,  96,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	192,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy0;
yy1:	++YYCURSOR;
yy0:
	if((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *YYCURSOR;
	if(yych <= '\n'){
		if(yych <= '\000')	goto yy4;
		if(yych <= '\t')	goto yy8;
		goto yy6;
	} else {
		if(yych != '-')	goto yy8;
	}
yy2:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych == '-')	goto yy13;
yy3:
#line 216
	{   YYPOS(0);
                        goto Document; 
                    }
yy4:	yych = *++YYCURSOR;
yy5:
#line 207
	{   SyckLevel *lvl = CURRENT_LEVEL();
                        ENSURE_IEND(lvl, -1);
                        return 0; 
                    }
yy6:	yych = *++YYCURSOR;
	goto yy10;
yy7:
#line 212
	{   int indt_len;
                        GOBBLE_UP_INDENT( indt_len, YYTOKEN );
                        goto Header; }
yy8:	yych = *++YYCURSOR;
	goto yy3;
yy9:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy10:	if(yybm[0+yych] & 32)	goto yy9;
	if(yych != ' ')	goto yy7;
yy11:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy12:	if(yybm[0+yych] & 64)	goto yy11;
	goto yy7;
yy13:	yych = *++YYCURSOR;
	if(yych == '-')	goto yy15;
yy14:	YYCURSOR = YYMARKER;
	switch(yyaccept){
	case 0:	goto yy3;
	}
yy15:	yych = *++YYCURSOR;
	if(yybm[0+yych] & 128)	goto yy16;
	if(yych == '\n')	goto yy19;
	goto yy14;
yy16:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy17:	if(yybm[0+yych] & 128)	goto yy16;
yy18:
#line 193
	{   SyckLevel *lvl = CURRENT_LEVEL();
                        if ( lvl->status == syck_lvl_header )
                        {
                            YYPOS(3);
                            goto Directive; 
                        }
                        else
                        {
                            ENSURE_IEND(lvl, -1);
                            YYPOS(0);
                            return 0; 
                        }
                    }
yy19:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy20:	if(yych == '\n')	goto yy19;
	goto yy18;
}
#line 220


Document:
    {
        SyckLevel *lvl = CURRENT_LEVEL();
        if ( lvl->status == syck_lvl_header )
        {
            lvl->status = syck_lvl_doc;
        }

        YYTOKEN = YYCURSOR;

{
	YYCTYPE yych;
	unsigned int yyaccept;
	static unsigned char yybm[] = {
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0, 160,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	136,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,  16,   0,  16,  64,  64, 
	 80,  80,  80,  80,  80,  80,  80,  80, 
	 80,  80,  64,  64,  64,  64,  64,  64, 
	 64,  64,  64,  64,  64,  64,  64,  64, 
	 64,  64,  64,  64,  64,  64,  64,  64, 
	 64,  64,  64,  64,  64,  64,  64,  64, 
	 64,  64,  64,  64,  64,  64,  64,  64, 
	  0,  64,  64,  64,  64,  64,  64,  64, 
	 64,  64,  64,  64,  64,  64,  64,  64, 
	 64,  64,  64,  64,  64,  64,  64,  64, 
	 64,  64,  64,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy21;
yy22:	++YYCURSOR;
yy21:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= ','){
		if(yych <= '"'){
			if(yych <= '\n'){
				if(yych <= '\000')	goto yy45;
				if(yych <= '\t')	goto yy47;
			} else {
				if(yych <= '\037')	goto yy47;
				if(yych <= ' ')	goto yy43;
				if(yych <= '!')	goto yy34;
				goto yy38;
			}
		} else {
			if(yych <= '\''){
				if(yych <= '#')	goto yy41;
				if(yych <= '%')	goto yy47;
				if(yych <= '&')	goto yy32;
				goto yy36;
			} else {
				if(yych == '*')	goto yy33;
				if(yych <= '+')	goto yy47;
				goto yy29;
			}
		}
	} else {
		if(yych <= 'Z'){
			if(yych <= ':'){
				if(yych <= '-')	goto yy31;
				if(yych <= '9')	goto yy47;
				goto yy29;
			} else {
				if(yych <= '=')	goto yy47;
				if(yych <= '>')	goto yy40;
				if(yych <= '?')	goto yy31;
				goto yy47;
			}
		} else {
			if(yych <= 'z'){
				if(yych <= '[')	goto yy25;
				if(yych == ']')	goto yy27;
				goto yy47;
			} else {
				if(yych <= '{')	goto yy25;
				if(yych <= '|')	goto yy40;
				if(yych <= '}')	goto yy27;
				goto yy47;
			}
		}
	}
yy23:	yych = *++YYCURSOR;
	goto yy75;
yy24:
#line 234
	{   // Isolate spaces
                        int indt_len;
                        GOBBLE_UP_INDENT( indt_len, YYTOKEN );
                        lvl = CURRENT_LEVEL();

                        // Check for open indent
                        ENSURE_IEND(lvl, indt_len);
                        ENSURE_IOPEN(lvl, indt_len, 0);
                        return INDENT;
                    }
yy25:	yych = *++YYCURSOR;
yy26:
#line 245
	{   ENSURE_IOPEN(lvl, 0, 1);
                        lvl = CURRENT_LEVEL();
                        ADD_LEVEL(lvl->spaces + 1, syck_lvl_inline);
                        return YYTOKEN[0]; 
                    }
yy27:	yych = *++YYCURSOR;
yy28:
#line 251
	{   POP_LEVEL();
                        return YYTOKEN[0]; 
                    }
yy29:	yych = *++YYCURSOR;
	if(yych == '\n')	goto yy72;
	if(yych == ' ')	goto yy69;
yy30:
#line 290
	{   ENSURE_IOPEN(lvl, 0, 1);
                        goto Plain; 
                    }
yy31:	yych = *++YYCURSOR;
	if(yych == '\n')	goto yy67;
	if(yych == ' ')	goto yy64;
	goto yy30;
yy32:	yych = *++YYCURSOR;
	if(yych <= '-')	goto yy30;
	if(yych == '`')	goto yy30;
	if(yych <= 'z')	goto yy61;
	goto yy30;
yy33:	yych = *++YYCURSOR;
	if(yybm[0+yych] & 64)	goto yy58;
	goto yy30;
yy34:	yych = *++YYCURSOR;
yy35:
#line 274
	{   goto TransferMethod; }
yy36:	yych = *++YYCURSOR;
yy37:
#line 276
	{   goto SingleQuote; }
yy38:	yych = *++YYCURSOR;
yy39:
#line 278
	{   goto DoubleQuote; }
yy40:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yybm[0+yych] & 32)	goto yy56;
	if(yych <= '+'){
		if(yych == ' ')	goto yy53;
		if(yych <= '*')	goto yy30;
		goto yy50;
	} else {
		if(yych <= '-'){
			if(yych <= ',')	goto yy30;
			goto yy50;
		} else {
			if(yych <= '/')	goto yy30;
			if(yych <= '9')	goto yy50;
			goto yy30;
		}
	}
yy41:	yych = *++YYCURSOR;
yy42:
#line 282
	{   goto Comment; }
yy43:	yych = *++YYCURSOR;
	goto yy49;
yy44:
#line 284
	{   goto Document; }
yy45:	yych = *++YYCURSOR;
yy46:
#line 286
	{   ENSURE_IEND(lvl, -1);
                        return 0; 
                    }
yy47:	yych = *++YYCURSOR;
	goto yy30;
yy48:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy49:	if(yybm[0+yych] & 8)	goto yy48;
	goto yy44;
yy50:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy51:	if(yybm[0+yych] & 32)	goto yy56;
	if(yych <= '+'){
		if(yych == ' ')	goto yy53;
		if(yych >= '+')	goto yy50;
	} else {
		if(yych <= '-'){
			if(yych >= '-')	goto yy50;
		} else {
			if(yych <= '/')	goto yy52;
			if(yych <= '9')	goto yy50;
		}
	}
yy52:	YYCURSOR = YYMARKER;
	switch(yyaccept){
	case 0:	goto yy30;
	}
yy53:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy54:	if(yych == ' ')	goto yy53;
yy55:
#line 280
	{   YYCURSOR--; goto ScalarBlock; }
yy56:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy57:	if(yybm[0+yych] & 32)	goto yy56;
	goto yy55;
yy58:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy59:	if(yybm[0+yych] & 64)	goto yy58;
yy60:
#line 270
	{   yylval->name = syck_strndup( YYTOKEN + 1, YYCURSOR - YYTOKEN - 1 );
                        return ALIAS;
                    }
yy61:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy62:	if(yych <= '-')	goto yy63;
	if(yych == '`')	goto yy63;
	if(yych <= 'z')	goto yy61;
yy63:
#line 266
	{   yylval->name = syck_strndup( YYTOKEN + 1, YYCURSOR - YYTOKEN - 1 );
                        return ANCHOR;
                    }
yy64:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy65:	if(yych == ' ')	goto yy64;
yy66:
#line 259
	{   ENSURE_IOPEN(lvl, YYTOKEN - YYLINEPTR, 1);
                        FORCE_NEXT_TOKEN(IOPEN);
                        ADD_LEVEL(YYCURSOR - YYLINEPTR, syck_lvl_doc);
                        YYCURSOR--; 
                        return YYTOKEN[0]; 
                    }
yy67:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy68:	if(yych == '\n')	goto yy67;
	goto yy66;
yy69:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy70:	if(yych == ' ')	goto yy69;
yy71:
#line 255
	{   YYPOS(1); 
                        return YYTOKEN[0]; 
                    }
yy72:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy73:	if(yych == '\n')	goto yy72;
	goto yy71;
yy74:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy75:	if(yych == '\n')	goto yy74;
	if(yych != ' ')	goto yy24;
yy76:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy77:	if(yybm[0+yych] & 128)	goto yy76;
	goto yy24;
}
#line 294

    }

Directive:
    {
        YYTOKTMP = YYCURSOR;

{
	YYCTYPE yych;
	unsigned int yyaccept;
	static unsigned char yybm[] = {
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	 32,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0, 192, 192, 
	192, 192, 192, 192, 192, 192, 192, 192, 
	192, 192, 128, 192, 192, 192, 192, 192, 
	192, 192, 192, 192, 192, 192, 192, 192, 
	192, 192, 192, 192, 192, 192, 192, 192, 
	192, 192, 192, 192, 192, 192, 192, 192, 
	192, 192, 192, 192, 192, 192, 192, 192, 
	  0, 192, 192, 192, 192, 192, 192, 192, 
	192, 192, 192, 192, 192, 192, 192, 192, 
	192, 192, 192, 192, 192, 192, 192, 192, 
	192, 192, 192,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy78;
yy79:	++YYCURSOR;
yy78:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= ' '){
		if(yych <= '\000')	goto yy80;
		if(yych <= '\037')	goto yy85;
		goto yy83;
	} else {
		if(yych == '%')	goto yy81;
		goto yy85;
	}
yy80:	YYCURSOR = YYMARKER;
	switch(yyaccept){
	case 0:	goto yy82;
	}
yy81:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych <= '-')	goto yy82;
	if(yych == '`')	goto yy82;
	if(yych <= 'z')	goto yy88;
yy82:
#line 307
	{   YYCURSOR = YYTOKTMP;
                        return DOCSEP;
                    }
yy83:	yych = *++YYCURSOR;
	goto yy87;
yy84:
#line 305
	{   goto Directive; }
yy85:	yych = *++YYCURSOR;
	goto yy82;
yy86:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy87:	if(yybm[0+yych] & 32)	goto yy86;
	goto yy84;
yy88:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy89:	if(yybm[0+yych] & 64)	goto yy88;
	if(yych != ':')	goto yy80;
yy90:	yych = *++YYCURSOR;
	if(yybm[0+yych] & 128)	goto yy91;
	goto yy80;
yy91:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy92:	if(yybm[0+yych] & 128)	goto yy91;
yy93:
#line 303
	{   goto Directive; }
}
#line 310


    }

Plain:
    {
        SyckLevel *plvl;
        YYCURSOR = YYTOKEN;
        plvl = CURRENT_LEVEL();

Plain2: 
        YYTOKTMP = YYCURSOR;

Plain3:

{
	YYCTYPE yych;
	unsigned int yyaccept;
	static unsigned char yybm[] = {
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0, 128,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	 64,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy94;
yy95:	++YYCURSOR;
yy94:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= ','){
		if(yych <= '\n'){
			if(yych <= '\000')	goto yy101;
			if(yych <= '\t')	goto yy107;
			goto yy103;
		} else {
			if(yych == ' ')	goto yy105;
			if(yych <= '+')	goto yy107;
			goto yy100;
		}
	} else {
		if(yych <= '\\'){
			if(yych != ':')	goto yy107;
		} else {
			if(yych <= ']')	goto yy98;
			if(yych == '}')	goto yy98;
			goto yy107;
		}
	}
yy96:	yych = *++YYCURSOR;
	if(yych == '\n')	goto yy119;
	if(yych == ' ')	goto yy116;
yy97:
#line 339
	{   goto Plain2; }
yy98:	yych = *++YYCURSOR;
yy99:
#line 329
	{   if ( plvl->status != syck_lvl_inline ) goto Plain2;
                        RETURN_IMPLICIT();
                    }
yy100:	yych = *++YYCURSOR;
	if(yych == '\n')	goto yy114;
	if(yych == ' ')	goto yy112;
	goto yy97;
yy101:	yych = *++YYCURSOR;
yy102:
#line 333
	{   RETURN_IMPLICIT(); }
yy103:	yych = *++YYCURSOR;
	goto yy111;
yy104:
#line 335
	{   RETURN_IMPLICIT(); }
yy105:	yych = *++YYCURSOR;
	goto yy109;
yy106:
#line 337
	{   goto Plain3; }
yy107:	yych = *++YYCURSOR;
	goto yy97;
yy108:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy109:	if(yybm[0+yych] & 64)	goto yy108;
	goto yy106;
yy110:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy111:	if(yybm[0+yych] & 128)	goto yy110;
	goto yy104;
yy112:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy113:	if(yych == ' ')	goto yy112;
	goto yy99;
yy114:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy115:	if(yych == '\n')	goto yy114;
	goto yy99;
yy116:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy117:	if(yych == ' ')	goto yy116;
yy118:
#line 327
	{   RETURN_IMPLICIT(); }
yy119:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy120:	if(yych == '\n')	goto yy119;
	goto yy118;
}
#line 341

    }

Comment:
    {
        YYTOKTMP = YYCURSOR;

{
	YYCTYPE yych;
	unsigned int yyaccept;
	static unsigned char yybm[] = {
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0, 128,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy121;
yy122:	++YYCURSOR;
yy121:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '\000')	goto yy123;
	if(yych == '\n')	goto yy125;
	goto yy126;
yy123:	yych = *++YYCURSOR;
yy124:
#line 350
	{   YYCURSOR = YYTOKTMP;
                        goto Document; 
                    }
yy125:	yych = *++YYCURSOR;
	goto yy129;
yy126:	yych = *++YYCURSOR;
yy127:
#line 354
	{   goto Comment; 
                    }
yy128:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy129:	if(yybm[0+yych] & 128)	goto yy128;
	goto yy124;
}
#line 357


    }

SingleQuote:
    {
        int qidx = 0;
        int qcapa = 100;
        char *qstr = S_ALLOC_N( char, qcapa );

SingleQuote2:

{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy130;
yy131:	++YYCURSOR;
yy130:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '\000')	goto yy134;
	if(yych != '\'')	goto yy135;
yy132:	yych = *++YYCURSOR;
	if(yych == '\'')	goto yy137;
yy133:
#line 375
	{   SyckNode *n = syck_alloc_str();
                        n->data.str->ptr = qstr;
                        n->data.str->len = qidx;
                        yylval->nodeData = n;
                        return PLAIN; 
                    }
yy134:	yych = *++YYCURSOR;
	goto yy133;
yy135:	yych = *++YYCURSOR;
yy136:
#line 382
	{   QUOTECAT(qstr, qcapa, qidx, *(YYCURSOR - 1)); 
                        goto SingleQuote2; 
                    }
yy137:	yych = *++YYCURSOR;
yy138:
#line 371
	{   QUOTECAT(qstr, qcapa, qidx, '\'');
                        goto SingleQuote2; 
                    }
}
#line 386


    }


DoubleQuote:
    {
        int qidx = 0;
        int qcapa = 100;
        char *qstr = S_ALLOC_N( char, qcapa );

DoubleQuote2:

{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy139;
yy140:	++YYCURSOR;
yy139:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '"'){
		if(yych <= '\000')	goto yy143;
		if(yych <= '!')	goto yy146;
		goto yy145;
	} else {
		if(yych != '\\')	goto yy146;
	}
yy141:	yych = *++YYCURSOR;
	if(yych == '"')	goto yy147;
yy142:
#line 412
	{   QUOTECAT(qstr, qcapa, qidx, *(YYCURSOR - 1)); 
                        goto DoubleQuote2; 
                    }
yy143:	yych = *++YYCURSOR;
yy144:
#line 405
	{   SyckNode *n = syck_alloc_str();
                        n->data.str->ptr = qstr;
                        n->data.str->len = qidx;
                        yylval->nodeData = n;
                        return PLAIN; 
                    }
yy145:	yych = *++YYCURSOR;
	goto yy144;
yy146:	yych = *++YYCURSOR;
	goto yy142;
yy147:	yych = *++YYCURSOR;
yy148:
#line 401
	{   QUOTECAT(qstr, qcapa, qidx, '"');
                        goto DoubleQuote2; 
                    }
}
#line 416

    }

TransferMethod:
    {
        YYTOKTMP = YYCURSOR;

{
	YYCTYPE yych;
	unsigned int yyaccept;
	static unsigned char yybm[] = {
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,  64,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	128,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy149;
yy150:	++YYCURSOR;
yy149:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '\n'){
		if(yych <= '\000')	goto yy151;
		if(yych <= '\t')	goto yy155;
		goto yy154;
	} else {
		if(yych == ' ')	goto yy152;
		goto yy155;
	}
yy151:yy152:	yych = *++YYCURSOR;
	goto yy160;
yy153:
#line 425
	{   SyckLevel *lvl;
                        YYCURSOR = YYTOKTMP;
                        if ( YYCURSOR == YYTOKEN + 1 )
                        {
                            return ITRANSFER;
                        }

                        lvl = CURRENT_LEVEL();

                        //
                        // URL Prefixing
                        //
                        if ( *(YYTOKEN + 1) == '^' )
                        {
                            yylval->name = S_ALLOC_N( char, YYCURSOR - YYTOKEN + strlen( lvl->domain ) );
                            yylval->name[0] = '\0';
                            strcat( yylval->name, lvl->domain );
                            strncat( yylval->name, YYTOKEN + 2, YYCURSOR - YYTOKEN - 2 );
                        }
                        else
                        {
                            char *carat = YYTOKEN + 1;
                            while ( (++carat) < YYCURSOR )
                            {
                                if ( *carat == '^' )
                                    break;
                            }

                            if ( carat < YYCURSOR )
                            {
                                lvl->domain = syck_strndup( YYTOKEN + 1, carat - YYTOKEN - 1 );
                                yylval->name = S_ALLOC_N( char, YYCURSOR - carat + strlen( lvl->domain ) );
                                yylval->name[0] = '\0';
                                strcat( yylval->name, lvl->domain );
                                strncat( yylval->name, carat + 1, YYCURSOR - carat - 1 );
                            }
                            else
                            {
                                yylval->name = syck_strndup( YYTOKEN + 1, YYCURSOR - YYTOKEN - 1 );
                            }
                        }
                        return TRANSFER; 
                    }
yy154:	yych = *++YYCURSOR;
	goto yy158;
yy155:	yych = *++YYCURSOR;
yy156:
#line 469
	{   goto TransferMethod; }
yy157:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy158:	if(yybm[0+yych] & 64)	goto yy157;
	goto yy153;
yy159:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy160:	if(yybm[0+yych] & 128)	goto yy159;
	goto yy153;
}
#line 471

    }

ScalarBlock:
    {
        int blockType = 0;
        int nlDoWhat = 0;
        int forceIndent = -1;
        char *yyt = YYTOKEN;
        switch ( *yyt )
        {
            case '|': blockType = BLOCK_LIT; break;
            case '>': blockType = BLOCK_FOLD; break;
        }

        while ( ++yyt <= YYCURSOR )
        {
            if ( *yyt == '-' )
            {
                nlDoWhat = NL_CHOMP;
            }
            else if ( *yyt == '+' )
            {
                nlDoWhat = NL_KEEP;
            }
            else if ( isdigit( *yyt ) )
            {
                forceIndent = strtol( yyt, NULL, 10 ) + ( YYTOKEN - YYLINEPTR );
            }
        }

        YYTOKEN = YYCURSOR;

ScalarBlock2:
        YYTOKTMP = YYCURSOR;

{
	YYCTYPE yych;
	unsigned int yyaccept;
	static unsigned char yybm[] = {
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0, 192,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	128,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy161;
yy162:	++YYCURSOR;
yy161:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '\000')	goto yy165;
	if(yych != '\n')	goto yy167;
yy163:	yych = *++YYCURSOR;
	goto yy170;
yy164:
#line 509
	{   int indt_len;
                        SyckLevel *lvl;
                        GOBBLE_UP_INDENT( indt_len, YYTOKTMP );
                        lvl = CURRENT_LEVEL();

                        if ( indt_len > lvl->spaces && lvl->status != syck_lvl_block )
                        {
                            ADD_LEVEL( forceIndent > 0 ? forceIndent : indt_len, syck_lvl_block );
                        }
                        else if ( indt_len < lvl->spaces )
                        {
                            YYCURSOR--;
                            yylval->nodeData = syck_new_str2( YYTOKEN, YYCURSOR - YYTOKEN );  
                            syck_fold_format( yylval->nodeData->data.str, blockType, lvl->spaces, nlDoWhat );
                            POP_LEVEL();
                            return BLOCK;
                        }
                        goto ScalarBlock2;
                    }
yy165:	yych = *++YYCURSOR;
yy166:
#line 530
	{   SyckLevel *lvl = CURRENT_LEVEL();
                        YYCURSOR--;
                        yylval->nodeData = syck_new_str2( YYTOKEN, YYCURSOR - YYTOKEN );  
                        syck_fold_format( yylval->nodeData->data.str, blockType, lvl->spaces, nlDoWhat );
                        POP_LEVEL();
                        return BLOCK; 
                    }
yy167:	yych = *++YYCURSOR;
yy168:
#line 538
	{   goto ScalarBlock2; }
yy169:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy170:	if(yybm[0+yych] & 64)	goto yy169;
	if(yych != ' ')	goto yy164;
yy171:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy172:	if(yybm[0+yych] & 128)	goto yy171;
	goto yy164;
}
#line 540

    }

}

int 
yywrap()
{
    return 1;
}

void 
yyerror( char *msg )
{
    if ( syck_parser_ptr->error_handler == NULL )
        syck_parser_ptr->error_handler = syck_default_error_handler;

    syck_parser_ptr->root = NULL;
    (syck_parser_ptr->error_handler)(syck_parser_ptr, msg);
}

