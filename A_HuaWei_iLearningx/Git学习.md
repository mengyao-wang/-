## 上传仓库

1. github 新建项目

2. 本地新建文件夹

3. git clone XXX, 文件夹内会出现.git文件夹，表明已经初始化过了，如果没有git clone，那就git init命令初始化

    eg. git clone https://github.com/mengyao-wang/Note.git

4. 本地文件夹内容修改

5. `git add .`

6. `git commit -m "自己的注释"`

7. `git remote add origin git@github.com:mengyao-wang/Note.git`

8. `git push -u origin "分支名"`

    eg.  git push -u origin main

    此命令可能会遇到的问题：

    ​		git@github.com: Permission denied (publickey).
    ​		fatal: 无法读取远程仓库。

    处理办法：

    （1）运行 `ssh git@github.com`，然后报错`git@github.com: Permission denied (publickey).`

    ​	  解决办法： 

    ​				先检查本地有没有id_rsa.pub，后来发现有，但是在github网站的Settings中，SSH为空，于是就把id_rsa.pub的内容复制到新建的SSH中即可。此时再运行上述命令，得到结果如下，表示成功：
    PTY allocation request failed on channel 0
    Hi mengyao-wang! You've successfully authenticated, but GitHub does not provide shell access.
    Connection to github.com closed.

    （2）再去git push -u origin "分支名"即可。



## 分支

概念：

​		分支是源代码管理的一个核心概念，它允许我们将工作划分为不同的分支，这样我们就可以自由地处理源代码，而不会影响其他人的工作或主分支中的实际代码。

- 对于Git，在新版本中主分支为main，之前版本为master。
- Git 允许创建任意数量的分支，且不必总是从主分支创建分支，我们可以从任何其他分支创建新分支。
- 分为**本地分支**和**远程分支**

### 查看分支

`git branch`

用法：git branch [<选项>] [-r | -a] [--merged | --no-merged]
   或：git branch [<选项>] [-l] [-f] <分支名> [<起始点>]
   或：git branch [<选项>] [-r] (-d | -D) <分支名>...
   或：git branch [<选项>] (-m | -M) [<旧分支>] <新分支>
   或：git branch [<选项>] (-c | -C) [<老分支>] <新分支>
   或：git branch [<选项>] [-r | -a] [--points-at]
   或：git branch [<选项>] [-r | -a] [--format]

通用选项
    -v, --verbose         显示哈希值和主题，若参数出现两次则显示上游分支
    -q, --quiet           不显示信息
    -t, --track           设置跟踪模式（参见 git-pull(1)）
    -u, --set-upstream-to <上游>
                          改变上游信息
    --unset-upstream      取消上游信息的设置
    --color[=<何时>]      使用彩色输出
    -r, --remotes         作用于远程跟踪分支
    --contains <提交>     只打印包含该提交的分支
    --no-contains <提交>  只打印不包含该提交的分支
    --abbrev[=<n>]        用 <n> 位数字显示 SHA-1 哈希值

具体的 git-branch 动作：
    **-a, --all             列出远程跟踪及本地分支**
    -**d, --delete          删除完全合并的分支**
    **-D                    删除分支（即使没有合并）**
    -m, --move            移动/重命名一个分支，以及它的引用日志
    -M                    移动/重命名一个分支，即使目标已存在
    -c, --copy            拷贝一个分支和它的引用日志
    -C                    拷贝一个分支，即使目标已存在
    --list                列出分支名
    -l, --create-reflog   创建分支的引用日志
    --edit-description    标记分支的描述
    -f, --force           强制创建、移动/重命名、删除
    --merged <提交>       只打印已经合并的分支
    --no-merged <提交>    只打印尚未合并的分支
    --column[=<风格>]     以列的方式显示分支
    --sort <key>          排序的字段名
    --points-at <对象>    只打印指向该对象的分支
    -i, --ignore-case     排序和过滤属于大小写不敏感
    --format <格式>       输出格式





git branch -a  没有远程分支，解决：先执行 git fetch

删除远程分支，git push origin --delete  "远程分支名"

### 切换分支

` git checkout (branch) `   切换到要修改的分支







