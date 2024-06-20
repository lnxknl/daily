#!/bin/bash

# 指定文件夹路径
folder_path="/home/tong/bin/chatlog/linux"

# 检查文件夹是否存在
if [ ! -d "$folder_path" ]; then
    echo "指定的文件夹不存在: $folder_path"
    exit 1
fi

# 获取文件夹中所有文件的列表
files=($(ls "$folder_path"))

# 检查是否有文件
if [ ${#files[@]} -eq 0 ]; then
    echo "文件夹中没有文件: $folder_path"
    exit 1
fi

# 随机选择一个文件
random_file=${files[$((RANDOM % ${#files[@]}))]}

# 使用vim打开随机文件
cd $folder_path
cat $random_file |less -i

