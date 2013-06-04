@ECHO off
SETLOCAL EnableExtensions
CD /D %~p0

SET sdkPath=E:\Repositories\FlexSimModuleSDK\VisualStudioWizards
SET flexsimContentSrcPath=%sdkPath%\FlexSimModuleDLLWizard\FlexsimModuleDLLWizard\Templates\1033\flexsimcontent
SET flexsimContentDestPath=%projectPath%\flexsimcontent

CD flexsimcontent
COPY /Y "%flexsimContentSrcPath%\*"