
## Git sub modules

Add submodule
``` bash
git submodule add <repository_url> <path/to/submodule>
git submodule update --init --recursive
git add .gitmodules submodule-folder
git commit -m "Added submodule"
```

Remove submodule
``` bash
vim .gitmodules
git rm --cached path/to/submodule
rm -rf path/to/submodule
vim .git/config
git add .gitmodules
git commit -m "Removed submodule"
```