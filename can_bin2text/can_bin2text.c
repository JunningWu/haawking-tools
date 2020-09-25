/*
 * Copyright (c) 2020 Beijing Haawking Technology Co.,Ltd
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Junning Wu
 * Email: junning.wu@mail.haawking.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i,j;
	unsigned char *buf;
	unsigned long FileLen;
	FILE *fp_in,*fp_out;
	j = argc;
	printf("===============================================================\n");
	printf("***Usage: Created by Junning Wu.\n");
	printf("***Usage: Converting Bin to CAN Boot Table.\n");
	printf("***Usage: ./bin2canboot file.bin file.txt\n");
	printf("===============================================================\n");
	if(j != 3 ){
		printf("!!! Please Input the Correct Aguments.\n");
		return 0;
	}
	printf("Input file:%s, Output File: %s\n",argv[1],argv[2]);
	fp_in = fopen(argv[1],"rb");
	fp_out = fopen(argv[2],"w");
	fseek(fp_in,0,SEEK_END);
	FileLen = ftell(fp_in);
	fseek(fp_in,0,SEEK_SET);
	printf("Total Bytes of Input File: %ld.\n",FileLen);
	buf = (unsigned char*)malloc(FileLen+1);

    fread(buf,1,FileLen,fp_in);
    if(strcmp(argv[1],"CANBOOT.bin") == 0){
      fprintf(fp_out,"序号 传输方向 接收时间标识 帧ID 帧格式 帧类型 数据长度 数据\n");
      printf("序号 传输方向 接收时间标识 帧ID 帧格式 帧类型 数据长度 数据\n");
      for(i=1;i<FileLen+1;i=i+2){
        fprintf(fp_out,"%d\t\t发送   12:08:46.618.0          0x00000001  数据帧  标准帧  0x02       %02x %02x \n", (i-1)/2,buf[i],buf[i-1]);
        printf("%d\t\t发送   12:08:46.618.0          0x00000001  数据帧  标准帧  0x02       %02x %02x \n", (i-1)/2,buf[i],buf[i-1]);
      }//End of For
    }//End of if

	fclose(fp_in);
	fclose(fp_out);
	free(buf);
    return 0;
}
