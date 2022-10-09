#ifndef __IOT_H__
#define __IOT_H__

extern int upload_sensor_data(const char *ip, const char *device, const char *sensor, const char *id, double data);
extern int download_sensor_status(const char *ip, const char *device, const char *sensor, const char *id);
extern int upload_sensor_status(const char *ip, const char *device, const char *sensor, const char *id, char *status);
extern int upload_device_datas(const char *ip, const char *device, const char *id, int sensor_id_arrary[], double sensor_data_arrary[], int size);

#endif





