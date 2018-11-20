#ifndef SO_FILE_H_
#define SO_FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 返回值为写入的len */
extern int write_value_to_file(const char* fileName, char* buff);
extern int write_intvalue_to_file(const char* fileName, int value) ;
extern int read_value_from_file(const char* fileName, char* buff, int len);
extern int read_intvalue_from_file(const char* fileName);


#ifdef __cplusplus
}
#endif


#endif 
