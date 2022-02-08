import os,shutil

hou_zhui = ['.jpg','.png','.JPG','.PNG']

count = 1
abspath = 'E:\\Download\\IDM\\兔玩\\'
def dfs(path):
    global count
    dir_list = os.listdir(path)
    for file_name in dir_list:
        if file_name[-4:] in hou_zhui:
            shutil.copy(path+file_name,f"E:\\Download\\IDM\\all\\{count}.jpg")
            count += 1
        elif os.path.isdir(path+file_name):
            dfs(path+file_name+'\\')


if __name__ == '__main__':
    dfs('E:\\Download\\IDM\\兔玩\\')
