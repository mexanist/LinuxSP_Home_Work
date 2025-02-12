#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/moduleparam.h>
#include <linux/timekeeping.h>

static struct kobject *mymodule;
static int myvariable = 0;

module_param(myvariable, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myvariable, "An integer");

static ssize_t myvariable_show(struct kobject *kobj,
                               struct kobj_attribute *attr, char *buf) {
        return sprintf(buf, "%d\n", myvariable);
}

static ssize_t myvariable_store(struct kobject *kobj,
                                struct kobj_attribute *attr, char *buf,
                                size_t count) {
        sscanf(buf, "%du", &myvariable);
        return count;
}

static struct kobj_attribute myvariable_attribute =
        __ATTR(myvariable, 0660, myvariable_show, (void *)myvariable_store);

static int __init mymodule_init(void) {
/* получение времени инициализации */
        int error = 0;
        struct timespec64 now;
        ktime_get_real_ts64(&now);

        pr_info("mymodule: initialised\n");
        pr_info("mymodule: initialised at %lld.%.9ld\n", (long long)now.tv_sec, now.tv_nsec);

        mymodule = kobject_create_and_add("mymodule", kernel_kobj);
        if (!mymodule)
                return -ENOMEM;

        error = sysfs_create_file(mymodule, &myvariable_attribute.attr);
        if (error) {
                pr_info("failed to create the myvariable file "
                        "in /sys/kernel/mymodule\n");
                kobject_put(mymodule);
                return error;
        }
        return error;
}

static void __exit mymodule_exit(void) {
/* получение времени деинициализации */
        struct timespec64 now;
        ktime_get_real_ts64(&now);

        pr_info("mymodule: Exit success\n");
        pr_info("mymodule: exited at %lld.%.9ld\n", (long long)now.tv_sec, now.tv_nsec);

        kobject_put(mymodule);
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL");
