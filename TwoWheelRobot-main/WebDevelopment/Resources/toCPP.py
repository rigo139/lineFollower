import os

EOL = "\n"

while(1):
    try:
        path     = input("Path to file: ")
        varName  = input("Variable name: ").upper()

        file = open( path, 'rb' )

        size = file.seek(0, os.SEEK_END)
        file.seek(0)
        data = '''#pragma once

#include <stdint.h>
#include <pgmspace.h>

'''
        data += "#pragma region " + varName + EOL + EOL
        data += "#define " + varName + "_SIZE " + str(size) + EOL
        data += "const uint8_t " + varName + "[] PROGMEM = {" + EOL + "\t"
        MAX_COL = 16
        colCounter = 0
        for i in range( size ):
            thisByte = file.read(1).hex()
            byteStr  = "0x" + thisByte
            data += byteStr
            if( i != size-1 ):
                data += ", "
            colCounter += 1
            if(colCounter >= MAX_COL):
                colCounter = 0
                data += EOL + "\t"
        data += "};" + EOL + EOL
        file.close()
        data += "#pragma endregion //" + varName + EOL + EOL

        #pathOut = path[:-4] + ".cpp"
        pathOut = varName + '.h'
        print( pathOut )
        with open(pathOut, 'w') as file:
            file.write( data )
        print(f"Data saved in {pathOut}\r\n")
    except Exception as err:
        print(err)
        
