# Generated by Django 2.1.5 on 2019-01-19 22:55

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('boards', '0007_post_amount'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='post',
            name='amount',
        ),
    ]
