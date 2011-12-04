#include <CL/cl.h>
#include "erl_nif.h"

static ERL_NIF_TERM nif_cl_info(ErlNifEnv* env,
					 int argc,
					 const ERL_NIF_TERM argv[])
{
  cl_uint num_entries;
  cl_uint num_platforms;
  cl_platform_id *platforms;
  cl_uint i;
  ERL_NIF_TERM res, profile, ver, name, vendor, ext, dev;

  clGetPlatformIDs(0, NULL, &num_platforms);
  platforms = (cl_platform_id *) malloc(sizeof(cl_platform_id)*num_platforms);
  clGetPlatformIDs(num_platforms, platforms, NULL);
  res = enif_make_list(env, 0);

  for(i=0; i<num_platforms; i++){
    char param_profile[100];
    profile = enif_make_list(env, 0);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, sizeof(param_profile), &param_profile, NULL);
    profile = enif_make_list_cell(env, enif_make_string(env, param_profile, ERL_NIF_LATIN1), profile);
    profile = enif_make_list_cell(env, enif_make_atom(env, "profile"), profile);

    char param_ver[100];
    ver = enif_make_list(env, 0);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, sizeof(param_ver), &param_ver, NULL);
    ver = enif_make_list_cell(env, enif_make_string(env, param_ver, ERL_NIF_LATIN1), ver);
    ver = enif_make_list_cell(env, enif_make_atom(env, "version"), ver);

    char param_name[100];
    name = enif_make_list(env, 0);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(param_name), &param_name, NULL);
    name = enif_make_list_cell(env, enif_make_string(env, param_name, ERL_NIF_LATIN1), name);
    name = enif_make_list_cell(env, enif_make_atom(env, "name"), name);

    char param_vendor[100];
    vendor = enif_make_list(env, 0);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(param_vendor), &param_vendor, NULL);
    vendor = enif_make_list_cell(env, enif_make_string(env, param_vendor, ERL_NIF_LATIN1), vendor);
    vendor = enif_make_list_cell(env, enif_make_atom(env, "vendor"), vendor);

    char param_ext[100];
    ext = enif_make_list(env, 0);
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(param_ext), &param_ext, NULL);
    ext = enif_make_list_cell(env, enif_make_string(env, param_ext, ERL_NIF_LATIN1), ext);
    ext = enif_make_list_cell(env, enif_make_atom(env, "extensions"), ext);

    dev = enif_make_list(env, 0);
    cl_uint param_dev;
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &param_dev); 
    dev = enif_make_list_cell(env, enif_make_int(env, param_dev), dev);
    dev = enif_make_list_cell(env, enif_make_atom(env, "devices"), dev);
  }
  free(platforms);
  res = enif_make_list_cell(env, dev, res);
  res = enif_make_list_cell(env, ext, res);
  res = enif_make_list_cell(env, vendor, res);
  res = enif_make_list_cell(env, name, res);
  res = enif_make_list_cell(env, ver, res);
  res = enif_make_list_cell(env, profile, res);
  return res;
}

static ErlNifFunc nif_funcs[] =
  {  
    {"cl_info", 0, nif_cl_info},
  };

ERL_NIF_INIT(clif,nif_funcs,NULL,NULL,NULL,NULL)
