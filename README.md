# Debian-Remote-Docker

A Debian Container Powered by XRDP.

## Environment Variables

There are several environment variables that can be enabled/adjusted.

| Name            | Description                                                     | Expected Value  |
| --------------- | :-------------------------------------------------------------- | --------------- |
| DIS_ROOT        | Disable root user                                               | "yes"           |
| ROOT_PASSWD     | Set root password.<br />Useless if DIS_ROOT enabled.            | string          |
| GUEST_ACC       | Enable guest account.<br />Username: guest<br />Password: guest | "yes"           |
| NEW_USER        | Add new user.<br />Set username to new user.                    | string          |
| NEW_USER_PASSWD | Set NEW_USER password.<br />Useless if NEW_USER unset.          | string          |
| NEW_USER_SUDO   | Add NEW_USER to sudo group.<br />Useless if NEW_USER unset.     | "yes"           |
| TZ              | Set timezone.                                                   | timezone string |

## Releases

The images is released in Docker Hub [riyangarma33/debian-remote](https://hub.docker.com/r/riyangarma33/debian-remote). The images have several tags formations. As long as the Desktop Environment is not in tags, the default is XFCE.

### latest

Default tag that been published. Builded from debian:bookworm.

### `<ADDITIONAL APPS>`

Debian Bookworm with user choice of additional apps.

### `<DEBIAN VERSION>`

User choice of debian version.

### `<DEBIAN VERSION>`-`<DESKTOP ENVIRONMENT>`

User choice of debian version and desktop environment.

### `<DEBIAN VERSION>`-`<ADDITIONAL APPS>`

User choice of debian version and additional apps.

### `<DEBIAN VERSION>`-`<DESKTOP ENVIRONMENT>`-`<ADDITIONAL APPS>`

User choice of debian version, desktop environment, and additional apps.

### slim

Slim variant of image. Builded from debian:bookworm-slim.

### slim-`<DESKTOP ENVIRONMENT>`

Slim variant of Debian Bookworm with user choice of desktop environment.

### slim-`<ADDITIONAL APPS>`

Slim variant of Debian Bookworm with user choice of additional apps.

### slim-`<DESKTOP ENVIRONMENT>`-`<ADDITIONAL APPS>`

Slim variant of Debian Bookworm with user choice of desktop environment and additional apps.

### `<DEBIAN VERSION>`-slim

User choice of debian version with slim variant.

### `<DEBIAN VERSION>`-slim-`<DESKTOP ENVIRONMENT>`

User choice of debian version and desktop environment with slim variant.

### `<DEBIAN VERSION>`-slim-`<DESKTOP ENVIRONMENT>`-`<ADDITIONAL APPS>`

User choice of debian version, desktop environment and additional apps with slim variant.
