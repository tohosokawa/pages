# Develop environment Settings

## git

### Show current git branch in bash prompt

Download `git-prompt.sh` to your home directory.

```bash
cd ~
# download git-prompt.sh
wget -O .git-prompt.sh https://raw.githubusercontent.com/git/git/master/contrib/completion/git-prompt.sh
# or 
curl -o .git-prompt.sh https://raw.githubusercontent.com/git/git/master/contrib/completion/git-prompt.sh
```

Add the following line to the end of `.bashrc`

```bash
source ~/.git-prompt.sh
```

- Chromebook crostini case

Original format

```bash
user@host:workspace$ 
```

Changed format

```bash
user@host:workspace (branch name)$ 
```

Modify `.bashrc`

```bash
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
# Add the following lines
    PS1=${PS1::-3}  # remove last 3 characters(\$ )
    PS1=${PS1}'\[\033[01;31m\]$(__git_ps1 " (%s)")\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
```
