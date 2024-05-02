//scripts/Game/Map/Modded/SCR_XX_MapMarker.c

//------------------------------------------------------------------------------------------------
/*!
This example draws a single simple marker on map. 

Copy the file to //scripts/Game/Map/Modded/SCR_XX_MapMarker.c

For proper use, you probably want to have it as a class class SCR_XX_MapMarker : SCR_MapUIBaseComponent . 
Remember to add the UI component to your map config (MapFullscreen.conf). 
- Override the official one in to your mod project
- Add your class under UI Components
*/

const string XX_MISSION_MARKER = "{2984D5F19FA61B6E}UI/Textures/Icons/InventoryHints/InventoryHint_SuppliesAvailable.edds";
const string XX_MISSION_LAYOUT = "{DD15734EB89D74E2}UI/layouts/Map/MapMarkerBase.layout";

modded class SCR_MapUIBaseComponent
{
	static SCR_MapEntity m_MapEntity;
	static bool m_isMapOpen = false;
	static ref Widget m_widget;
	
	//------------------------------------------------------------------------------------------------
	override void OnMapOpen(MapConfiguration config)
	{
		super.OnMapOpen(config);
		
		if (!m_isMapOpen)
		{
			CreateMarker();
			m_isMapOpen = true;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override protected void OnMapClose(MapConfiguration config)
	{
		m_isMapOpen = false;
		super.OnMapClose(config);
	}
	
	//------------------------------------------------------------------------------------------------
	override void Update(float timeSlice)
	{
		super.Update(timeSlice);

		if (!m_isMapOpen)
			return;
		
		m_MapEntity = SCR_MapEntity.GetMapInstance();
		if (!m_MapEntity) 
			return;

		int screenPosX;
		int screenPosY;
		
		vector pos = "7000 0 5000";
		
		m_MapEntity.WorldToScreen(pos[0], pos[2], screenPosX, screenPosY, true);
		ImageWidget m_UnitImage = ImageWidget.Cast(m_widget.FindAnyWidget("Image"));
		
		screenPosX = GetGame().GetWorkspace().DPIUnscale(screenPosX);
		screenPosY = GetGame().GetWorkspace().DPIUnscale(screenPosY);
				
		FrameSlot.SetPos(
				m_widget, 
				screenPosX,
				screenPosY
		);		
	}

	//------------------------------------------------------------------------------------------------
	protected void CreateMarker()
	{
		m_widget = GetGame().GetWorkspace().CreateWidgets(XX_MISSION_LAYOUT, m_RootWidget);
		
		if (!m_widget) 
			return;

		ImageWidget widgetImage = ImageWidget.Cast(m_widget.FindAnyWidget("MarkerIcon"));		
		if(widgetImage)
		{
			widgetImage.LoadImageTexture(0, XX_MISSION_MARKER);
//			widgetImage.SetColor(Color.FromRGBA(255, 0, 0, 255));
			widgetImage.SetVisible(true);
		}
		
		TextWidget widgetText = TextWidget.Cast(m_widget.FindAnyWidget("MarkerText"));
		if(widgetText)
		{
			widgetText.SetText("Simple marker");
//			widgetText.SetColor(Color.FromRGBA(0, 255, 0, 255));
			widgetText.SetVisible(true);
		}		
	}
}