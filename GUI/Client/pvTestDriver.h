/*=========================================================================

  Program:   Visualization Toolkit
  Module:    pvTestDriver.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME pvTestDriver - A program to run paraview for testing mpi and server modes.
// .SECTION Description
// 


#ifndef __pvTestDriver_h
#define __pvTestDriver_h

#include <vtkstd/string>
#include <vtkstd/vector>
#include <kwsys/Process.h>
#include <kwsys/stl/string>
#include <kwsys/stl/vector>

class pvTestDriver 
{
public:
  int Main(int argc, char* argv[]);
  pvTestDriver();
  ~pvTestDriver();

protected:
  void SeparateArguments(const char* str, 
                         vtkstd::vector<vtkstd::string>& flags);
  
  void ReportCommand(const char* const* command, const char* name);
  int ReportStatus(kwsysProcess* process, const char* name);
  int ProcessCommandLine(int argc, char* argv[]);
  void CollectConfiguredOptions();
  void CreateCommandLine(kwsys_stl::vector<const char*>& commandLine,
                         const char* paraView,
                         const char* paraviewFlags, 
                         const char* numProc,
                         int argStart=0,
                         int argCount=0,
                         char* argv[]=0);
  
  int StartServer(kwsysProcess* server, const char* name,
                  vtkstd::vector<char>& out, vtkstd::vector<char>& err);
  int OutputStringHasError(const char* pname, vtkstd::string& output);

  int WaitForLine(kwsysProcess* process, vtkstd::string& line, double timeout,
                  vtkstd::vector<char>& out, vtkstd::vector<char>& err);
  void PrintLine(const char* pname, const char* line);
  int WaitForAndPrintLine(const char* pname, kwsysProcess* process,
                          vtkstd::string& line, double timeout,
                          vtkstd::vector<char>& out, vtkstd::vector<char>& err,
                          int* foundWaiting);
private:
  // fullpath to paraview executable
  vtkstd::string ParaView;
  // fullpath to paraview server executable
  vtkstd::string ParaViewServer;
  // fullpath to paraview renderserver executable
  vtkstd::string ParaViewRenderServer;
  // fullpath to mpirun executable
  vtkstd::string MPIRun;

  // This specify the preflags and post flags that can be set using:
  // VTK_MPI_PREFLAGS / VTK_MPI_POSTFLAGS at config time
  vtkstd::vector<vtkstd::string> MPIPreFlags;
  vtkstd::vector<vtkstd::string> MPIPostFlags;
  
  // MPIClientFlags / MPIServerFlags allows you to specify flags specific for 
  // the client or the server
  vtkstd::vector<vtkstd::string> MPIClientFlags;
  vtkstd::vector<vtkstd::string> MPIServerFlags;
  
  // Specify the number of process flag, this can be set using: VTK_MPI_NUMPROC_FLAG. 
  // This is then split into : 
  // MPIClientNumProcessFlag, MPIServerNumProcessFlag & MPIRenderServerNumProcessFlag
  vtkstd::string MPINumProcessFlag;
  vtkstd::string MPIClientNumProcessFlag;
  vtkstd::string MPIServerNumProcessFlag;
  vtkstd::string MPIRenderServerNumProcessFlag;

  vtkstd::string CurrentPrintLineName;

  int RenderServerNumProcesses;
  double TimeOut;
  int TestRenderServer;
  int TestServer;
  int ArgStart;
  int AllowErrorInOutput;
  
  // Specify if the -rc flag was passed or not
  int ReverseConnection;
};

#endif

