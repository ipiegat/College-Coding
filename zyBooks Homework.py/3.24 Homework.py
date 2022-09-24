koala = (
    """
             |       :     . |
             | '  :      '   |
             |  .  |   '  |  |
   .--._ _...:.._ _.--. ,  ' |
  (  ,  `        `  ,  )   . |
   '-/              \-'  |   |
     |  o   /\   o  |       :|
     \     _\/_     / :  '   |
     /'._   ^^   _.;___      |
   /`    `"""
    """`      `\=   |
 /`                     /=  .|
;             '--,-----'=    |
|                 `\  |    . |
\                   \___ :   |
/'.                     `\=  |
\_/`--......_            /=  |
            |`-.        /= : |
            | : `-.__ /` .   |
            |    .   ` |    '|
            |  .  : `   . |  |"""
)


def exec_2(f):
    f()
    f()


def exec_4(f):
    exec_2(f)
    exec_2(f)


# define a new function here that prints out the koala once


def f():
    print(koala, end="")


# use your function and exec_4 to draw 4 koala bears!

exec_4(f)
