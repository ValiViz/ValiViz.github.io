---
title: 基于Hexo和GitHub Pages的个人博客部署
date: 2024-03-12 10:00:30
tags:
  - Hexo
  - GItHub
  - Git
  - Blog
categories: 
- 教程
index_img: /attachments/post_1/hexo.png
banner_img: /attachments/post_1/hexo.png
---
# 拥有GitHub账号

[GitHub: Let’s build from here](https://github.com)

# 搭建环境

## 创建GitHub仓库

创建仓库名为`username（注意替换）.github.io`的GitHub仓库，不附带README.md文件。

## 安装git

[git](https://git-scm.com/)

## 安装Node.js

[Node.js](https://nodejs.org/en)

## 安装Hexo

在本地选择一个路径，新建博客文件夹`blog/`，在博客文件夹内右键空白处，选择`Open Git Bash here`，输入：

```bash
$ npm install -g hexo-cli
$ hexo init
```

# 远程连接

```bash
$ ls -al ~/.ssh
$ ssh-keygen -t ed25519 -C "useremail@example.com（注意替换）"
（三次回车）
$ cat ~/.ssh/id_ed25519.pub
```

将打印出的公钥右键Copy。

GitHub -> 头像 -> Settings -> SSH and GPG keys -> New SSH Key

在Title栏取名，在Key栏粘贴刚才复制的公钥，Add SSH Key。

## 验证连接

```bash
$ ssh -T git@github.com
```

如果匹配指纹`SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU`，则输入：

```bash
yes
```

# 第一次推送

## 修改git配置

登录git，修改配置以使用main作为默认分支名称：

```bash
$ git config --global user.email "useremail@example.com（注意替换）"
$ git config --global user.name "username（注意替换）"
$ git config --global init.defaultBranch main
```

## 新建git仓库并建立连接

```bash
$ git init
$ git remote add origin git@github.com:username/username.github.io.git（注意替换）
```

## 推送

```bash
$ git add --all
$ git commit -m "Add source files"
$ git push -u origin main
```

# 第二次推送

开辟新分支 gh-pages 用于展示由 main 生成的网页，将“由 main 生成网页推送到 gh-pages”这一过程交给 GitHub Actions 自动完成，为此新建文件 `blog/.github/workflows/pages.yml`，内容如下：

```yml
name: Pages

on:
  push:
    branches:
      - main # default branch

jobs:
  pages:
    runs-on: ubuntu-latest
    permissions:
      contents: write
    steps:
      - uses: actions/checkout@v2
      - name: Use Node.js 20.x.x（注意替换）
        uses: actions/setup-node@v2
        with:
          node-version: "20（注意替换）"
      - name: Cache NPM dependencies
        uses: actions/cache@v2
        with:
          path: node_modules
          key: ${{ runner.OS }}-npm-cache
          restore-keys: |
            ${{ runner.OS }}-npm-cache
      - name: Install Dependencies
        run: npm install
      - name: Build
        run: npm run build
      - name: Deploy
        uses: peaceiris/actions-gh-pages@v3
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./public
```

其中Node.js的版本号可以通过以下途径得知：
1. 安装Node.js时下载的安装包名称中包含版本号；
2. `win`+`R` -> `cmd` -> `确定` -> `node -v`;
3. `$ mode -v`。

## 反解耦合设计

在blog/的`.gitignore`文件中删去`node_modules/`，以解决本地资源文件与远程仓库不同步的问题。

{% note warning %}
原设计的目的是解耦，以实现模块化和规范化，**但我不会！！！**
有能力者另请参阅[^3]中`缺失之环-β`章节。
{% endnote %}

## 推送

```bash
$ git add --all
$ git commit -m "Add workflows-pages.yml"
$ git push -u origin main
```

# 切换展示分支

GitHub -> 博客仓库 -> Settings -> Pages

Source: `Deploy from a branch`

Branch: `gh-pages` `/(root)`

点击`Save`。

# 结束语

在完成上述步骤后，访问`https://username.github.io`即可查看完成部署的博客页面。

---

# 参考链接

[^1]: [概述 | Hexo](https://hexo.io/zh-cn/docs/)
[^2]: [在 GitHub Pages 上部署 Hexo | Hexo](https://hexo.io/zh-cn/docs/github-pages)
[^3]: [Hexo 博客搭建指北 | KGL.BLOG)](https://kongolou.github.io/post/Hexo-博客搭建指北.html)
[^4]: [利用hexo在GItHub上建立个人博客？ - 知乎](https://www.zhihu.com/question/39326923/answer/3120401540)