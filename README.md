# Debian-Remote-Docker

## A Debian Container Powered by XRDP

## Environment Variables

There are several environment variables that can be enabled/adjusted.

| Name            | Description                                                     | Expected Value  |
| --------------- | :-------------------------------------------------------------- | --------------- |
| DIS_ROOT        | Disable root user                                               | "yes"           |
| ROOT_PASSWD     | Set root password.<br />Useless if DIS_ROOT enabled.            | string          |
| GUEST_ACC       | Enable guest account.<br />Username: guest<br />Password: guest | "yes"           |
| NEW_USER        | Add new user.<br />Set username to new user.                    | string          |
| NEW_USER_PASSWD | Set NEW_USER password.                                          | string          |
| NEW_USER_SUDO   | Add NEW_USER to sudo group.                                     | "yes"           |
| TZ              | Set timezone.                                                   | timezone string |
