#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

const bool chk_ignite()
{
    FILE *ignited = fopen("/ignited", "r");
    if (ignited == NULL)
        return false;
    else
    {
        char status[4];
        fscanf(ignited, "%s", status);
        // printf("First time configuration = %s\n", status);
        if (strcmp(status, "yes") == 0)
        {
            fclose(ignited);
            return true;
        }
        else
        {
            fclose(ignited);
            return false;
        }
    }
}

void set_ignite()
{
    FILE *ignited = fopen("/ignited", "w");
    fprintf(ignited, "yes\n");
    fclose(ignited);
}

char command[70];

void clear_command()
{
    memset(command, 0, sizeof(command));
}

int main()
{
    // Check if container is configured.
    if (!chk_ignite())
    {
        printf("First Time Configuration\n");
        char *DIS_ROOT = getenv("DIS_ROOT");
        if (DIS_ROOT != NULL && strcmp(DIS_ROOT, "yes") == 0)
        {
            system("passwd -l root");
            system("usermod -s /usr/sbin/nologin root");
            // Disable xrdp root login
            FILE *sesman = fopen("/etc/xrdp/sesman.ini", "r");
            FILE *sesman_new = fopen("/etc/xrdp/sesman_new.ini", "w");
            char sesman_buffer[100];
            while (fgets(sesman_buffer, 100, sesman) != NULL)
            {
                if (strstr(sesman_buffer, "AllowRootLogin") != NULL)
                    strcpy(sesman_buffer, "AllowRootLogin=false\n");
                fprintf(sesman_new, "%s", sesman_buffer);
            }
            fclose(sesman);
            fclose(sesman_new);
            memset(sesman_buffer, 0, sizeof(sesman_buffer));
            remove("/etc/xrdp/sesman.ini");
            rename("/etc/xrdp/sesman_new.ini", "/etc/xrdp/sesman.ini");
            DIS_ROOT = NULL;
        }
        else
        {
            // Configure root password
            char *ROOT_PASSWD = getenv("ROOT_PASSWD");
            if (ROOT_PASSWD != NULL && strlen(ROOT_PASSWD) > 0)
            {
                sprintf(command, "echo root:%s | chpasswd", ROOT_PASSWD);
                system(command);
                clear_command();
                unsetenv("ROOT_PASSWD");
                ROOT_PASSWD = NULL;
            }
            else
            {
                printf("Your root password is \'root\'\n");
                system("echo root:root | chpasswd");
            }
            printf("Root password has been set\n");
            system("chsh -s /usr/bin/fish");
        }
        // Configure Guest Account
        char *GUEST_ACC = getenv("GUEST_ACC");
        if (GUEST_ACC != NULL && strcmp(GUEST_ACC, "yes") == 0)
        {
            printf("Creating guest account\n");
            system("cp /bin/bash /bin/rbash");
            system("useradd -m -s /bin/rbash guest");
            system("echo guest:guest | chpasswd");
            printf("Set guest session directory to read only\n");
            if (mkdir("/home/guest/.cache") != 0 || mkdir("/home/guest/.cache/sessions") != 0)
                printf("session directory already exist!\n");
            else
                system("chown guest:guest -R /home/guest/.cache");
            system("chmod -w /home/guest/.cache/sessions");
            // system("mkdir /home/guest");
            // system("mkdir /home/guest/programs");
            // FILE *bash_profile = fopen("/home/guest/.bash_profile", "w");
            // // char *bash_pro_data = "# cat /home/localuser/.bash_profile\n# .bash_profile\n\n# Get the aliases and functions\nif [ -f ~/.bashrc ]; then\n. ~/.bashrc\nfi\n# User specific environment and startup programs\nreadonly PATH=$HOME/programs\nexport PATH\n";
            // char *bash_pro_data = "PATH=$HOME/bin\n";
            // fprintf(bash_profile, bash_pro_data);
            // bash_pro_data = NULL;
            // fclose(bash_profile);
            // system("chattr +i /home/guest/.bash_profile");

            // FILE *profile = fopen("/home/guest/.profile", "w");
            // char *bash_pro_data = "# cat /home/localuser/.profile\n# .profile\n\n# Get the aliases and functions\nif [ -f ~/.bashrc ]; then\n. ~/.bashrc\nfi\n# User specific environment and startup programs\nreadonly PATH=$HOME/programs\nexport PATH\n";
            // fprintf(profile, bash_pro_data);
            // bash_pro_data = NULL;
            // fclose(profile);
            // system("chattr +i /home/guest/.profile");
            // system("ln -s /usr/bin/date /home/guest/programs/");
            // system("ln -s /usr/bin/ls /home/guest/programs/");
            // system("ln -s /usr/bin/ping /home/guest/programs/");
            // system("ln -s /usr/bin/cat /home/guest/programs/");
        }
        GUEST_ACC = NULL;
        // Configure New User If Exist in ENV
        char *NEW_USER = getenv("NEW_USER");
        if (NEW_USER != NULL && strlen(NEW_USER) > 0)
        {
            printf("Adding new user\n");
            sprintf(command, "useradd -m -s /usr/bin/fish %s", NEW_USER);
            system(command);
            clear_command();
            // Configure New Password for New User
            char *NEW_USER_PASSWD = getenv("NEW_USER_PASSWD");
            if (NEW_USER_PASSWD != NULL && strlen(NEW_USER_PASSWD) > 0)
            {
                printf("Set new password for new user\n");
                sprintf(command, "echo %s:%s | chpasswd", NEW_USER, NEW_USER_PASSWD);
                system(command);
                clear_command();
                unsetenv("NEW_USER_PASSWD");
                NEW_USER_PASSWD = NULL;
            }
            // Add New User to Sudoers
            char *NEW_USER_SUDO = getenv("NEW_USER_SUDO");
            if (NEW_USER_SUDO != NULL && strcmp(NEW_USER_SUDO, "yes") == 0)
            {
                printf("Adding new user to sudo group\n");
                sprintf(command, "usermod -aG sudo %s", NEW_USER);
                system(command);
                clear_command();
                unsetenv("NEW_USER_SUDO");
            }
            unsetenv("NEW_USER");
            printf("New user has been added\n");
            NEW_USER = NULL;
        }
        // Change Timezone
        char *TZ = getenv("TZ");
        if (TZ != NULL && strlen(TZ) > 0)
        {
            printf("Changing timezone\n");
            sprintf(command, "ln -sf /usr/share/zoneinfo/%s /etc/localtime", TZ);
            system(command);
            clear_command();
            unsetenv("TZ");
            printf("Timezone has been changed to %s\n", TZ);
        }
        set_ignite();
    }
    else
    {
        printf("Container Has Been Configured\n");
        // system("service xrdp stop");
        system("systemctl enable xrdp");
    }
    // system("/lib/systemd/systemd");
    // system("service xrdp start");
    // system("/bin/bash");
    return 0;
}
