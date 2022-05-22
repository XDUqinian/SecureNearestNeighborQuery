from pyope.ope import OPE,ValueRange
cipher = OPE(b'long key' * 2, in_range=ValueRange(9999, 1000000),
                              out_range=ValueRange(1, 1000000))

if __name__ == '__main__':
    data=[]
    k=0
    with open("NE.txt", "r") as f:  # 打开文件
        file_data = f.readlines()  # 读取文件
        for row in file_data:
            tmp_list = row.split(' ')
            tmp_list[-1] = tmp_list[-1].replace('\n','') #去掉换行符
            tmp_list[0]=cipher.encrypt(int(float(tmp_list[0])*1000000))
            tmp_list[1]=cipher.encrypt(int(float(tmp_list[1])*1000000))
            print(k)
            k+=1
            data.append(tmp_list)
    with open("NE_encrypto.txt","w") as f:
        for i in data:
            for j in i:
                f.write(str(j))
                f.write(' ')
            f.write('\n')
