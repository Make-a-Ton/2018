# Generated by Django 2.1.5 on 2019-01-19 22:47

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('boards', '0004_auto_20190120_0417'),
    ]

    operations = [
        migrations.AlterField(
            model_name='post',
            name='amount',
            field=models.IntegerField(null=True),
        ),
    ]